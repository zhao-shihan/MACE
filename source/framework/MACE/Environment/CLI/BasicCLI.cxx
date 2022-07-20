#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Utility/VerboseLevel.hxx"
#include "MACE/Version.hxx"

#include <stdexcept>

namespace MACE::Environment::CLI {

bool BasicCLI::fgInstantiate = false;

BasicCLI::BasicCLI() :
    argparse::ArgumentParser({}, MACE_VERSION_STRING) {
    if (fgInstantiate) {
        throw std::logic_error("MACE::Environment::CLI::BasicCLI: Trying to construct CLI twice");
    }
    fgInstantiate = true;

    add_argument("-V", "--verbose")
        .scan<'i', int>()
        .default_value(static_cast<int>(Utility::VerboseLevel::Warning))
        .required()
        .help("set verbose level");
}

} // namespace MACE::Environment::CLI
