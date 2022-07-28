#include "MACE/Environment/CLI/SimulationG4CLI.hxx"

namespace MACE::Environment::CLI {

SimulationG4CLI::SimulationG4CLI() :
    BasicCLI() {
    fArgParser.add_argument("macro")
        .help("Run the program with it. If not provided or empty, run in interactive session with default initialization.")
        .default_value(std::string(""));
    fArgParser.add_argument("-i", "--interact")
        .help("Run in interactive session even if a macro is provided. The once provided macro will initialize the interactive session, override default.")
        .nargs(0);
}

} // namespace MACE::Environment::CLI
