#include "MACE/Cxx2b/ToUnderlying.hxx"
#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Version.hxx"

#include <iostream>
#include <stdexcept>

namespace MACE::Environment::CLI {

BasicCLI::BasicCLI() :
    CLIBase() {
    fArgParser.add_argument("-h", "--help")
        .help("Show help message and exit.")
        .nargs(0)
        .action([this](const auto&) {
            std::cout << fArgParser << std::flush;
            std::exit(EXIT_SUCCESS);
        });
    fArgParser.add_argument("-v", "--version")
        .help("Print version and exit.")
        .nargs(0)
        .action([](const auto&) {
            std::cout << MACE_VERSION_STRING << std::endl;
            std::exit(EXIT_SUCCESS);
        });
    fArgParser.add_argument("-V", "--verbose")
        .scan<'i', int>()
        .help("Set verbose level. (-1: quiet, 0: error, 1: warning, 2: verbose, 3: more verbose)")
        .action([](const std::string& argVerbose) {
            constexpr auto low = Cxx2b::ToUnderlying(VerboseLevel::Quiet);
            constexpr auto up = Cxx2b::ToUnderlying(VerboseLevel::MoreVerbose);
            auto parsedVerbose = Cxx2b::ToUnderlying(VerboseLevel::Undefined);
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

std::optional<VerboseLevel> BasicCLI::GetVerboseLevel() const {
    if (const auto optionalVerbose = fArgParser.present<std::underlying_type_t<VerboseLevel>>("-V");
        optionalVerbose.has_value()) {
        return static_cast<VerboseLevel>(optionalVerbose.value());
    } else {
        return std::nullopt;
    }
}

} // namespace MACE::Environment::CLI
