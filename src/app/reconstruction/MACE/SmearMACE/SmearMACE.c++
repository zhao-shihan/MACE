#include "MACE/Data/Sheet.h++"
#include "MACE/Env/BasicEnv.h++"
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
    Env::BasicEnv env{argc, argv, cli};

    UseXoshiro<512> random;

    const auto outputName{cli.OutputFilePath().generic_string()};
    {
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
        AppendConfigText("EMCSimHit", cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
        AppendConfigText("MCPSimHit", cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
        TFile file{outputName.c_str(), cli.OutputFileMode().c_str(), "", ROOT::RCompressionSetting::EDefaults::kUseGeneralPurpose};
        if (not file.IsOpen()) { throw std::runtime_error{fmt::format("Cannot open file '{}' with mode '{}'", outputName, cli.OutputFileMode())}; }
        MakeTextTMacro(smearingConfigText.str(), "SmearingConfig", "Print SmearMACE smearing configuration")->Write();
    }
    {
        SmearMACE::Smearer smearer{cli.InputFilePath(), outputName};
        const auto [iFirst, iLast]{cli.DatasetIndexRange()};
        const auto Smear{[&](const auto& nameFmt, const auto& smearingConfig, const auto& identity) {
            if (smearingConfig or identity) {
                for (auto i{iFirst}; i < iLast; ++i) {
                    smearer.Smear(fmt::vformat(nameFmt, fmt::make_format_args(i)), smearingConfig);
                }
            }
        }};
        Smear(cli.CDCSimHitNameFormat(), cli.CDCSimHitSmearingConfig(), cli.CDCSimHitIdentity());
        Smear(cli.CDCSimTrackNameFormat(), cli.CDCSimTrackSmearingConfig(), cli.CDCSimTrackIdentity());
        Smear(cli.EMCSimHitNameFormat(), cli.EMCSimHitSmearingConfig(), cli.EMCSimHitIdentity());
        Smear(cli.MCPSimHitNameFormat(), cli.MCPSimHitSmearingConfig(), cli.MCPSimHitIdentity());
    }

    return EXIT_SUCCESS;
}
