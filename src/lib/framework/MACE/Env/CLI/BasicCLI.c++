#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Version.h++"

#include <iostream>
#include <stdexcept>

namespace MACE::Env::CLI {

BasicCLI::BasicCLI() :
    CLIBase() {
    AddArgument("-h", "--help")
        .help("Show help message and exit.")
        .nargs(0)
        .action([this](const auto&) {
            std::cout << GetArgParser() << std::flush;
            std::exit(EXIT_SUCCESS);
        });
    AddArgument("-v", "--version")
        .help("Print version and exit.")
        .nargs(0)
        .action([](const auto&) {
            std::cout << MACE_VERSION_STRING << std::endl;
            std::exit(EXIT_SUCCESS);
        });
    AddArgument("-V", "--verbose")
        .scan<'i', int>()
        .help("Set verbose level. (-2: quiet, -1: error, 0: warning, 1: verbose, 2: more verbose)")
        .action([](const std::string& argVerbose) {
            constexpr auto low = std23::to_underlying(VL::Quiet);
            constexpr auto up = std23::to_underlying(VL::MoreVerbose);
            auto parsedVerbose = std23::to_underlying(VL::Undefined);
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

std::optional<VL> BasicCLI::GetVerboseLevel() const {
    if (const auto optionalVerbose = GetArgParser().present<std::underlying_type_t<VL>>("-V");
        optionalVerbose.has_value()) {
        return static_cast<VL>(optionalVerbose.value());
    } else {
        return std::nullopt;
    }
}

} // namespace MACE::Env::CLI
