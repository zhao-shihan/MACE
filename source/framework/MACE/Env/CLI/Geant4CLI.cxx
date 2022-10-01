#include "MACE/Env/CLI/Geant4CLI.hxx"

namespace MACE::Env::CLI {

Geant4CLI::Geant4CLI() :
    BasicCLI() {
    AddArgument("macro")
        .help("Run the program with it. If not provided or empty, run in interactive session with default initialization.")
        .default_value(std::string(""));
    AddArgument("-i", "--interact")
        .help("Run in interactive session even if a macro is provided. The once provided macro will initialize the interactive session, override default.")
        .nargs(0);
}

} // namespace MACE::Env::CLI
