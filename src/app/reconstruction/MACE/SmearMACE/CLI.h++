#pragma once

#include "MACE/Env/CLI/MonteCarloCLI.h++"

#include "gsl/gsl"

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

namespace MACE::SmearMACE {

class CLI final : public Env::CLI::MonteCarloCLI {
public:
    CLI();

    auto InputFilePath() const -> auto { return ArgParser().get<std::vector<std::string>>("input"); }
    auto OutputFileMode() const -> auto { return ArgParser().present("-m").value_or("NEW"); }
    auto OutputFilePath() const -> std::filesystem::path;

    auto DatasetIndexRange() const -> std::pair<gsl::index, gsl::index>;

    auto CDCSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--cdc-hit"); }
    auto CDCSimHitIdentity() const -> bool { return ArgParser().get<bool>("--cdc-hit-id"); }
    auto CDCSimHitNameFormat() const -> auto { return ArgParser().present("--cdc-hit-name").value_or("G4Run{}/CDCSimHit"); }

    auto CDCSimTrackSmearingConfig() const -> auto { return ParseSmearingConfig("--cdc-track"); }
    auto CDCSimTrackIdentity() const -> bool { return ArgParser().get<bool>("--cdc-track-id"); }
    auto CDCSimTrackNameFormat() const -> auto { return ArgParser().present("--cdc-track-name").value_or("G4Run{}/CDCSimTrack"); }

    auto EMCSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--emc-hit"); }
    auto EMCSimHitIdentity() const -> bool { return ArgParser().get<bool>("--emc-hit-id"); }
    auto EMCSimHitNameFormat() const -> auto { return ArgParser().present("--emc-hit-name").value_or("G4Run{}/EMCSimHit"); }

    auto MCPSimHitSmearingConfig() const -> auto { return ParseSmearingConfig("--mcp-hit"); }
    auto MCPSimHitIdentity() const -> bool { return ArgParser().get<bool>("--mcp-hit-id"); }
    auto MCPSimHitNameFormat() const -> auto { return ArgParser().present("--mcp-hit-name").value_or("G4Run{}/MCPSimHit"); }

private:
    auto ParseSmearingConfig(std::string_view arg) const -> std::optional<std::unordered_map<std::string, std::string>>;
};

} // namespace MACE::SmearMACE
