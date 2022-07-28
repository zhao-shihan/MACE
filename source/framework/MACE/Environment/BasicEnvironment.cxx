#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Version.hxx"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <system_error>

namespace MACE::Environment {

BasicEnvironment::BasicEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                                   VerboseLevel verboseLevel, bool printStartupMessage) :
    EnvironmentBase(),
    FreeSingleton<BasicEnvironment>(),
    fVerboseLevel(verboseLevel) {
    // CLI: do parse and get args
    if (optCLI.has_value()) {
        auto& cli = optCLI->get();
        // Parse
        cli.ParseArgs(argc, argv);
        // Get args
        fVerboseLevel = cli.GetVerboseLevel().value_or(verboseLevel);
    }
    // Print startup message after parse
    if (printStartupMessage) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
}

void BasicEnvironment::PrintStartupMessageSplitLine() const {
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(fVerboseLevel, Error, std::cout)
        << "\n===============================================================================\n"
        << std::endl;
}

void BasicEnvironment::PrintStartupMessageBody(int argc, char* argv[]) const {
    std::error_code cwdError;
    auto cwd = std::filesystem::current_path(cwdError).generic_string();
    if (cwdError) {
        cwd.assign("<Error getting current working directory>");
    }
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(fVerboseLevel, Error, std::cout)
        << " xxxx framework (MACE offline software system) " << MACE_VERSION_STRING << '\n'
        << " Copyright (c) 2020-2022 MACE software working group \n"
        << '\n'
        << " Exe: " << argv[0] << '\n'
        << " CWD: " << cwd << '\n';
    if (fVerboseLevel >= VerboseLevel::Verbose) {
        std::cout << "\n List of all " << argc << " command line arguments:\n";
        for (int i = 0; i < argc; ++i) {
            std::cout << "  argv[" << i << "]: " << argv[i] << '\n';
        }
    }
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(fVerboseLevel, Error, std::cout) << std::flush;
}

} // namespace MACE::Environment
