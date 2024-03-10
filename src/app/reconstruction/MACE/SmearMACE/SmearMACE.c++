#include "MACE/Data/Sheet.h++"
#include "MACE/SmearMACE/CLI.h++"
#include "MACE/Env/MPIEnv.h++"

#include <cstdlib>

auto main(int argc, char* argv[]) -> int {
    MACE::SmearMACE::CLI cli;
    MACE::Env::MPIEnv env{argc, argv, cli};

    fmt::println("{}", cli.InputFilePath().generic_string().c_str());
    fmt::println("{}", cli.OutputFilePath().generic_string().c_str());
    fmt::println("{}", cli.OutputFileOption());

    return EXIT_SUCCESS;
}
