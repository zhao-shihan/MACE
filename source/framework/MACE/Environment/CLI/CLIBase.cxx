#include "MACE/Environment/CLI/CLIBase.hxx"
#include "MACE/Version.hxx"

#include <stdexcept>

namespace MACE::Environment::CLI {

CLIBase::CLIBase() :
    NonMoveableBase(),
    fArguments(std::nullopt),
    fArgParser({}, MACE_VERSION_STRING, argparse::default_arguments::none) {
    if (static bool gInstantiated = false; gInstantiated) {
        throw std::logic_error("MACE::Environment::CLI::CLIBase: Trying to construct CLI twice");
    } else {
        gInstantiated = true;
    }
}

void CLIBase::ParseArgs(int argc, char* argv[]) {
    if (not Parsed()) {
        try {
            fArgParser.parse_args(argc, argv);
        } catch (const std::runtime_error& exception) {
            std::cerr << exception.what() << '\n'
                      << "Try: " << argv[0] << " --help" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        fArguments = {argc, argv};
    } else {
        ThrowParsed();
    }
}

const std::pair<int, char**>& CLIBase::GetArgcArgv() const {
    if (Parsed()) {
        return fArguments.value();
    } else {
        ThrowNotParsed();
    }
}

[[noreturn]] void CLIBase::ThrowParsed() {
    throw std::logic_error("MACE::Environment::CLI: Command line arguments has been parsed");
}

[[noreturn]] void CLIBase::ThrowNotParsed() {
    throw std::logic_error("MACE::Environment::CLI: Command line arguments has not been parsed");
}

} // namespace MACE::Environment::CLI
