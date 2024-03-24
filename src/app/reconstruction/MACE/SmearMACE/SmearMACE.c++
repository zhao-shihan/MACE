#include "MACE/Data/Sheet.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/Execution/Executor.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/SmearMACE/CLI.h++"
#include "MACE/SmearMACE/Smearer.h++"
#include "MACE/Utility/MPIReseedRandomEngine.h++"
#include "MACE/Utility/MakeTextTMacro.h++"
#include "MACE/Utility/UseXoshiro.h++"

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
    Env::MPIEnv env{argc, argv, cli};

    UseXoshiro<512> random;
    MPIReseedRandomEngine();

    const auto outputName{MPIX::ParallelizePath(cli.OutputFilePath()).generic_string()};
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
        AppendConfigText("CDCSimTrack", cli.CDCSimTrackSmearingConfig(), cli.CDCSimTrackIdentity());
        AppendConfigText("STCSimHit", cli.STCSimHitSmearingConfig(), cli.STCSimHitIdentity());
        AppendConfigText("MCPSimHit", cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
        AppendConfigText("EMCSimHit", cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
        MakeTextTMacro(smearingConfigText.str(), "SmearingConfig", "Print SmearMACE smearing configuration")->Write();
    }();
    {
        MPIX::Executor<unsigned> executor;
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
        Smear(cli.CDCSimTrackNameFormat(), cli.CDCSimTrackSmearingConfig(), cli.CDCSimTrackIdentity());
        Smear(cli.STCSimHitNameFormat(), cli.STCSimHitSmearingConfig(), cli.STCSimHitIdentity());
        Smear(cli.MCPSimHitNameFormat(), cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
        Smear(cli.EMCSimHitNameFormat(), cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
    }

    return EXIT_SUCCESS;
}
