#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Version.hxx"

#include <stdexcept>

namespace MACE::Environment::CLI {

bool BasicCLI::fgInstantiated = false;

BasicCLI::BasicCLI() :
    argparse::ArgumentParser({}, MACE_VERSION_STRING) {
    if (fgInstantiated) {
        throw std::logic_error("MACE::Environment::CLI::BasicCLI: Trying to construct CLI twice");
    }
    fgInstantiated = true;

    add_argument("-V", "--verbose")
        .scan<'i', int>()
        .default_value(static_cast<int>(VerboseLevel::Warning))
        .required()
        .help("sets verbose level");
}

VerboseLevel BasicCLI::GetVerboseLevel() {
    const auto parsedVerbose = get<int>("-V");
    const auto low = static_cast<int>(VerboseLevel::Quiet);
    const auto up = static_cast<int>(VerboseLevel::MoreVerbose);
    if (parsedVerbose < low or parsedVerbose > up) {
        throw std::invalid_argument(std::string("-V --verbose: value (")
                                        .append(std::to_string(parsedVerbose))
                                        .append(") out of range (")
                                        .append(std::to_string(low))
                                        .append(" ~ ")
                                        .append(std::to_string(up))
                                        .append(")"));
    }
    return static_cast<VerboseLevel>(parsedVerbose);
}

} // namespace MACE::Environment::CLI
