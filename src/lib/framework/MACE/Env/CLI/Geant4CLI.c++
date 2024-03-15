#include "MACE/Env/CLI/Geant4CLI.h++"

namespace MACE::Env::CLI {

Geant4CLI::Geant4CLI() :
    MonteCarloCLI{} {
    AddArgument("macro")
        .help("Run the program in batch session with it. If not provided, run in interactive session with default initialization.")
        .nargs(argparse::nargs_pattern::optional);
    AddArgument("-i", "--interactive")
        .help("Run in interactive session despite of a provided macro. The macro will initialize the session.")
        .nargs(0);
}

} // namespace MACE::Env::CLI
