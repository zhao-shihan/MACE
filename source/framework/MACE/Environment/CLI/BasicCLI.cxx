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
        .help("sets verbose level")
        .action([](const std::string& argVerbose) {
            constexpr auto low = static_cast<int>(VerboseLevel::Quiet);
            constexpr auto up = static_cast<int>(VerboseLevel::MoreVerbose);
            auto parsedVerbose = static_cast<int>(VerboseLevel::Undefined);
            std::from_chars(argVerbose.data(), argVerbose.data() + argVerbose.size(), parsedVerbose);
            if (parsedVerbose < low or parsedVerbose > up) {
                throw std::runtime_error(std::string("-V --verbose: '")
                                             .append(argVerbose)
                                             .append("' is invalid or out of range (")
                                             .append(std::to_string(low))
                                             .append(" ~ ")
                                             .append(std::to_string(up))
                                             .append(")"));
            }
            return parsedVerbose;
        });
}

} // namespace MACE::Environment::CLI
