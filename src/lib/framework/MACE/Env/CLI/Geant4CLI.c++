#include "MACE/Env/CLI/Geant4CLI.h++"

#include "CLHEP/Random/RandomEngine.h"

namespace MACE::Env::CLI {

Geant4CLI::Geant4CLI() :
    BasicCLI{} {
    AddArgument("macro")
        .help("Run the program with it. If not provided or empty, run in interactive session with default initialization.")
        .default_value(std::string{});
    AddArgument("-i", "--interactive")
        .help("Run in interactive session even if a macro is provided. The interactive session will be initialized with the provided macro.")
        .nargs(0);
    AddArgument("--seed")
        .help("Set random seed.")
        .scan<'i', long>();
}

auto Geant4CLI::Macro() const -> std::optional<std::string> {
    auto macro{ArgParser().get("macro")};
    if (macro.empty()) {
        return {};
    } else {
        return macro;
    }
}

auto Geant4CLI::Seed(CLHEP::HepRandomEngine& rng) const -> bool {
    auto seed{ArgParser().present<long>("--seed")};
    if (seed) {
        rng.setSeed(*seed, 3);
        return true;
    } else {
        return false;
    }
}

} // namespace MACE::Env::CLI
