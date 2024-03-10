#include "MACE/Env/CLI/CLIBase.h++"
#include "MACE/Version.h++"

#include <cstdlib>
#include <stdexcept>

namespace MACE::Env::CLI {

CLIBase::CLIBase() :
    NonMoveableBase{},
    fArgcArgv{},
    fArgParser{{}, MACE_VERSION_STRING, argparse::default_arguments::none} {
    if (static bool gInstantiated{}; gInstantiated) {
        throw std::logic_error{"MACE::Env::CLI::CLIBase: Trying to construct CLI twice"};
    } else {
        gInstantiated = true;
    }
}

auto CLIBase::ParseArgs(int argc, char* argv[]) -> void {
    if (not Parsed()) {
        try {
            fArgParser.parse_args(argc, argv);
        } catch (const std::runtime_error& exception) {
            std::cerr << exception.what() << '\n'
                      << "Try: " << argv[0] << " --help" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        fArgcArgv = {argc, argv};
    } else {
        ThrowParsed();
    }
}

auto CLIBase::ArgcArgv() const -> ArgcArgvType {
    if (Parsed()) {
        return fArgcArgv.value();
    } else {
        ThrowNotParsed();
    }
}

[[noreturn]] void CLIBase::ThrowParsed() {
    throw std::logic_error{"MACE::Env::CLI: Command line arguments has been parsed"};
}

[[noreturn]] void CLIBase::ThrowNotParsed() {
    throw std::logic_error{"MACE::Env::CLI: Command line arguments has not been parsed"};
}

} // namespace MACE::Env::CLI
