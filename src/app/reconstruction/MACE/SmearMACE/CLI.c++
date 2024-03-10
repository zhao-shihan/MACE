#include "MACE/SmearMACE/CLI.h++"

#include "fmt/format.h"

namespace MACE::SmearMACE {

CLI::CLI() :
    BasicCLI{} {
    AddArgument("input")
        .help("Input file path.");
    AddArgument("-o", "--output")
        .help("Output file path. Suffix on input file name by default.");
    AddArgument("-p", "--option")
        .help("Output file option. NEW by default.");
}

auto CLI::OutputFilePath() const -> std::filesystem::path {
    auto output{ArgParser().present("-o")};
    if (output) {
        return *std::move(output);
    } else {
        auto input{InputFilePath()};
        auto extension{input.extension().generic_string()};
        return fmt::format("{}_smeared{}", input.replace_extension().generic_string(), std::move(extension));
    }
}

} // namespace MACE::SmearMACE
