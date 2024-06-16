#include "Mustard/Data/Sheet.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/MPIX/Execution/Executor.h++"
#include "Mustard/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SmearMACE/CLI.h++"
#include "MACE/SmearMACE/Smearer.h++"
#include "Mustard/Utility/MPIReseedRandomEngine.h++"
#include "Mustard/Utility/MakeTextTMacro.h++"
#include "Mustard/Utility/UseXoshiro.h++"

#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TMacro.h"

#include "gsl/gsl"

#include "fmt/format.h"

#include <cstdlib>
#include <sstream>
#include <stdexcept>

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    SmearMACE::CLI cli;
    Mustard::Env::MPIEnv env{argc, argv, cli};

    Mustard::UseXoshiro<512> random;
    Mustard::MPIReseedRandomEngine();

    const auto outputName{Mustard::MPIX::ParallelizePath(cli.OutputFilePath()).generic_string()};
    [&] {
        TFile file{outputName.c_str(), cli.OutputFileMode().c_str(), "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose};
        if (not file.IsOpen()) { throw std::runtime_error{fmt::format("Cannot open file '{}' with mode '{}'", outputName, cli.OutputFileMode())}; }
        if (env.OnCommNodeWorker()) { return; }
        std::stringstream smearingConfigText;
        const auto AppendConfigText{[&](const auto& nameInConfigText, const auto& smearingConfig, const auto& identity) {
            if (not(smearingConfig or identity)) { return; }
            smearingConfigText << fmt::format("{}:\n", nameInConfigText);
            if (smearingConfig) {
                for (auto&& [var, smear] : *smearingConfig) {
                    smearingConfigText << fmt::format("  {}: {}\n", var, smear);
                }
            }
        }};
        AppendConfigText("CDCSimHit", cli.CDCSimHitSmearingConfig(), cli.CDCSimHitIdentity());
        AppendConfigText("TTCSimHit", cli.TTCSimHitSmearingConfig(), cli.TTCSimHitIdentity());
        AppendConfigText("MMSSimTrack", cli.MMSSimTrackSmearingConfig(), cli.MMSSimTrackIdentity());
        AppendConfigText("MCPSimHit", cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
        AppendConfigText("EMCSimHit", cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
        Mustard::MakeTextTMacro(smearingConfigText.str(), "SmearingConfig", "Print SmearMACE smearing configuration")->Write();
    }();
    {
        Mustard::MPIX::Executor<unsigned> executor;
        SmearMACE::Smearer smearer{cli.InputFilePath(), outputName, cli.BatchSize(), executor};
        const auto [iFirst, iLast]{cli.DatasetIndexRange()};
        const auto Smear{[&, iFirst = iFirst, iLast = iLast](const auto& nameFmt, const auto& smearingConfig, const auto& identity) {
            if (smearingConfig or identity) {
                for (auto i{iFirst}; i < iLast; ++i) {
                    smearer.Smear(fmt::vformat(nameFmt, fmt::make_format_args(i)), smearingConfig);
                }
            }
        }};
        Smear(cli.CDCSimHitNameFormat(), cli.CDCSimHitSmearingConfig(), cli.CDCSimHitIdentity());
        Smear(cli.TTCSimHitNameFormat(), cli.TTCSimHitSmearingConfig(), cli.TTCSimHitIdentity());
        Smear(cli.MMSSimTrackNameFormat(), cli.MMSSimTrackSmearingConfig(), cli.MMSSimTrackIdentity());
        Smear(cli.MCPSimHitNameFormat(), cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
        Smear(cli.EMCSimHitNameFormat(), cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
    }

    return EXIT_SUCCESS;
}
