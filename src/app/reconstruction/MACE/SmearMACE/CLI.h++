#pragma once

#include "MACE/Env/CLI/CLI.h++"
#include "MACE/Env/CLI/Module/BasicModule.h++"
#include "MACE/Env/CLI/Module/ModuleBase.h++"
#include "MACE/Env/CLI/Module/MonteCarloModule.h++"

#include "gsl/gsl"

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

namespace MACE::SmearMACE {

class CLIModule : public Env::CLI::ModuleBase {
public:
    CLIModule(argparse::ArgumentParser& argParser);

    auto InputFilePath() const -> auto { return ArgParser().get<std::vector<std::string>>("input"); }
    auto OutputFileMode() const -> auto { return ArgParser().present("-m").value_or("NEW"); }
    auto OutputFilePath() const -> std::filesystem::path;

    auto DatasetIndexRange() const -> std::pair<gsl::index, gsl::index>;
    auto BatchSize() const -> auto { return ArgParser().present<unsigned>("-b").value_or(10000); }

    auto CDCSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--cdc-hit"); }
    auto CDCSimHitIdentity() const -> bool { return ArgParser().get<bool>("--cdc-hit-id"); }
    auto CDCSimHitNameFormat() const -> auto { return ArgParser().present("--cdc-hit-name").value_or("G4Run{}/CDCSimHit"); }

    auto TTCSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--ttc-hit"); }
    auto TTCSimHitIdentity() const -> bool { return ArgParser().get<bool>("--ttc-hit-id"); }
    auto TTCSimHitNameFormat() const -> auto { return ArgParser().present("--ttc-hit-name").value_or("G4Run{}/TTCSimHit"); }

    auto MMSSimTrackSmearingConfig() const -> auto { return ParseSmearingConfig("--mms-track"); }
    auto MMSSimTrackIdentity() const -> bool { return ArgParser().get<bool>("--mms-track-id"); }
    auto MMSSimTrackNameFormat() const -> auto { return ArgParser().present("--mms-track-name").value_or("G4Run{}/MMSSimTrack"); }

    auto MCPSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--mcp-hit"); }
    auto MCPSimHitIdentity() const -> bool { return ArgParser().get<bool>("--mcp-hit-id"); }
    auto MCPSimHitNameFormat() const -> auto { return ArgParser().present("--mcp-hit-name").value_or("G4Run{}/MCPSimHit"); }

    auto EMCSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--emc-hit"); }
    auto EMCSimHitIdentity() const -> bool { return ArgParser().get<bool>("--emc-hit-id"); }
    auto EMCSimHitNameFormat() const -> auto { return ArgParser().present("--emc-hit-name").value_or("G4Run{}/EMCSimHit"); }

private:
    auto ParseSmearingConfig(std::string_view arg) const -> std::optional<std::unordered_map<std::string, std::string>>;
};

using CLI = Env::CLI::CLI<Env::CLI::BasicModule,
                          Env::CLI::MonteCarloModule,
                          CLIModule>;

} // namespace MACE::SmearMACE
