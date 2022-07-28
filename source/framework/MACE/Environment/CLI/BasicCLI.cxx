#include "MACE/Cxx2b/ToUnderlying.hxx"
#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Environment/VerboseLevel.hxx"
#include "MACE/Version.hxx"

#include <stdexcept>

namespace MACE::Environment::CLI {

BasicCLI::BasicCLI() :
    NonMoveableBase(),
    fArgParser({}, MACE_VERSION_STRING) {
    if (static bool gInstantiated = false; gInstantiated) {
        throw std::logic_error("MACE::Environment::CLI::BasicCLI: Trying to construct CLI twice");
    } else {
        gInstantiated = true;
    }

    fArgParser.add_argument("-V", "--verbose")
        .scan<'i', int>()
        .default_value(Cxx2b::ToUnderlying(VerboseLevel::Warning))
        .required()
        .help("sets verbose level (-1: quiet, 0: error, 1: warning, 2: verbose, 3: more verbose)")
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

void BasicCLI::ParseArgs(int argc, const char* const argv[]) {
    try {
        fArgParser.parse_args(argc, argv);
    } catch (const std::runtime_error& exception) {
        std::cerr << exception.what() << '\n'
                  << "Try: " << argv[0] << " --help" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

} // namespace MACE::Environment::CLI
