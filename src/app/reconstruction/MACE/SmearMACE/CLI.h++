#pragma once

#include "MACE/Env/CLI/BasicCLI.h++"

#include <filesystem>
#include <optional>
#include <string>

namespace MACE::SmearMACE {

class CLI final : public Env::CLI::BasicCLI {
public:
    CLI();

    auto InputFilePath() const -> std::filesystem::path { return ArgParser().get("input"); }
    auto OutputFilePath() const -> std::filesystem::path;
    auto OutputFileOption() const -> std::string { return ArgParser().present("-p").value_or("NEW"); }
};

} // namespace MACE::SmearMACE
