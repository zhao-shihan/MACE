#include "MACE/Environment/CLI/detail/CLIBase.hxx"
#include "MACE/Version.hxx"

#include <stdexcept>

namespace MACE::Environment::CLI::Detail {

CLIBase::CLIBase() :
    NonMoveableBase(),
    fArgParser({}, MACE_VERSION_STRING, argparse::default_arguments::none),
    fArguments(std::nullopt) {
    if (static bool gInstantiated = false; gInstantiated) {
        throw std::logic_error("MACE::Environment::CLI::Detail::CLIBase: Trying to construct CLI twice");
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
        throw std::logic_error("MACE::Environment::CLI::Detail::CLIBase::ParseArgs: Command line arguments has been parsed");
    }
}

int CLIBase::GetArgc() const {
    if (Parsed()) {
        return fArguments->first;
    } else {
        throw std::logic_error("MACE::Environment::CLI::Detail::CLIBase::GetArgc: Command line arguments has not been parsed");
    }
}

char** CLIBase::GetArgv() const {
    if (Parsed()) {
        return fArguments->second;
    } else {
        throw std::logic_error("MACE::Environment::CLI::Detail::CLIBase::GetArgv: Command line arguments has not been parsed");
    }
}

} // namespace MACE::Environment::CLI::Detail
