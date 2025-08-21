#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/GenICMD/GenICMD.h++"

#include "Mustard/CLHEPX/Random/Xoshiro.h++"
#include "Mustard/Data/GeneratedEvent.h++"
#include "Mustard/Data/Output.h++"
#include "Mustard/Env/CLI/MonteCarloCLI.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Execution/Executor.h++"
#include "Mustard/IO/File.h++"
#include "Mustard/IO/Print.h++"
#include "Mustard/Physics/Generator/InternalConversionMuonDecay.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/UseXoshiro.h++"

#include "muc/numeric"
#include "muc/utility"

#include <cmath>
#include <string>
#include <type_traits>

namespace MACE::GenICMD {

using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::PhysicalConstant;
using namespace std::string_literals;

GenICMD::GenICMD() :
    Subprogram{"GenICMD", "Generate internal conversion muon decay (mu->ennee) events for physical study or test."} {}

auto GenICMD::Main(int argc, char* argv[]) const -> int {
    Mustard::Env::CLI::MonteCarloCLI<> cli;
    cli->add_argument("n").help("Number of events to generate.").nargs(1).scan<'i', unsigned long long>();
    cli->add_argument("-o", "--output").help("Output file path.").default_value("mu2ennee.root"s).required().nargs(1);
    cli->add_argument("-m", "--output-mode").help("Output file creation mode (see ROOT documentation for details).").default_value("NEW"s).required().nargs(1);
    cli->add_argument("--compression-level").help("Output file compression level (see ROOT documentation for details).").default_value(muc::to_underlying(ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose)).required().nargs(1).scan<'i', std::underlying_type_t<ROOT::RCompressionSetting::EDefaults::EValues>>();
    cli->add_argument("-t", "--output-tree").help("Output tree name.").default_value("mu2ennee"s).required().nargs(1);
    cli->add_argument("-d", "--mcmc-delta").help("Step size in MCMC sampling.").required().nargs(1).scan<'g', double>();
    cli->add_argument("-x", "--mcmc-discard").help("Number of states discarded between two samples in MCMC sampling.").required().nargs(1).scan<'i', int>();
    cli->add_argument("-p", "--polarization").help("Parent particle polarization vector").required().nargs(3).scan<'g', double>();
    auto& cliMG0{cli->add_mutually_exclusive_group()};
    cliMG0.add_argument("--ep-ek-upper-bound").help("Add upper bound for atomic positron kinetic energy.").nargs(1).scan<'g', double>();
    cliMG0.add_argument("--bias").help("Enable MACE detector bias (importance sampling).").flag();
    cli->add_argument("--pxy-softening-factor").help("Softening factor for transverse momentum soft comparision in bias.").default_value(0.5_MeV).required().nargs(1).scan<'g', double>();
    cli->add_argument("--cos-theta-softening-factor").help("Softening factor for momentum cosine soft comparision in bias.").default_value(0.1).required().nargs(1).scan<'g', double>();
    cli->add_argument("--ep-ek-softening-factor").help("Softening factor for energetic positron kinetic energy soft comparision in bias.").default_value(1_keV).required().nargs(1).scan<'g', double>();
    Mustard::Env::MPIEnv env{argc, argv, cli};

    Mustard::UseXoshiro<256> random;
    cli.SeedRandomIfFlagged();

    Mustard::File<TFile> file{cli->get("--output"), cli->get("--output-mode")};
    Mustard::Data::Output<Mustard::Data::GeneratedKinematics> writer{cli->get("--output-tree")};

    const auto polarization{cli->get<std::vector<double>>("--polarization")};
    Mustard::InternalConversionMuonDecay generator("mu+", {polarization[0], polarization[1], polarization[2]},
                                                   cli->get<double>("--mcmc-delta"), cli->get<int>("--mcmc-discard"));

    if (cli->present("--ep-ek-upper-bound")) {
        generator.Bias(
            [epEkUpperBound = cli->get<double>("--ep-ek-upper-bound")](auto&& momenta) {
                const auto& [p, p1, p2, k1, k2]{momenta};
                return p.e() < electron_mass_c2 + epEkUpperBound;
            });
    } else if (cli["--bias"] == true) {
        generator.Bias(
            [scPxy = muc::soft_cmp{cli->get<double>("--pxy-softening-factor")},
             scCos = muc::soft_cmp{cli->get<double>("--cos-theta-softening-factor")},
             scEk = muc::soft_cmp{cli->get<double>("--ep-ek-softening-factor")}](auto&& momenta) {
                const auto& cdc{Detector::Description::CDC::Instance()};
                const auto& ttc{Detector::Description::TTC::Instance()};
                const auto mmsB{Detector::Description::MMSField::Instance().FastField()};
                const auto inPxyCut{scPxy((cdc.GasInnerRadius() / 2) * mmsB * c_light)};
                const auto outPxyCut{scPxy((ttc.Radius() / 2) * mmsB * c_light)};
                const auto cosCut{scCos(1 / muc::hypot(2 * cdc.GasOuterRadius() / cdc.GasOuterLength(), 1.))};

                // .         e+ n   n   e-  e+
                const auto& [p, _1, _2, p1, p2]{momenta};
                const auto pLow{scEk(p.e() - electron_mass_c2) < scEk(0)};
                const auto p1Seen{scPxy(muc::hypot(p1.x(), p1.y())) > outPxyCut and scCos(muc::abs(p1.cosTheta())) < cosCut};
                const auto p2Miss{scPxy(muc::hypot(p2.x(), p2.y())) < inPxyCut or scCos(muc::abs(p2.cosTheta())) > cosCut};
                return pLow and p1Seen and p2Miss;
            });
    }

    Mustard::MasterPrint("Burning-in, please wait...");
    generator.BurnIn();
    Mustard::MasterPrintLn(" Done.");

    Mustard::Executor<unsigned long long> executor;
    executor(cli->get<unsigned long long>("n"), [&](auto) {
        const auto [weight, pdgID, p]{generator()};
        Mustard::Data::Tuple<Mustard::Data::GeneratedKinematics> event;
        // 0: e+, 3: e-, 4: e+
        Get<"pdgID">(event) = {pdgID[0], pdgID[3], pdgID[4]};
        Get<"px">(event) = {float(p[0].x()), float(p[3].x()), float(p[4].x())};
        Get<"py">(event) = {float(p[0].y()), float(p[3].y()), float(p[4].y())};
        Get<"pz">(event) = {float(p[0].z()), float(p[3].z()), float(p[4].z())};
        Get<"w">(event) = weight;
        writer.Fill(event);
    });
    executor.PrintExecutionSummary();

    writer.Write();

    return EXIT_SUCCESS;
}

} // namespace MACE::GenICMD
