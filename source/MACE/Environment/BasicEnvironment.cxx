#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Version.hxx"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <system_error>

namespace MACE::Environment {

ObserverPtr<BasicEnvironment> BasicEnvironment::fgBasicEnvironmentInstance = nullptr;
bool BasicEnvironment::fgBasicEnvironmentFinalized = false;

BasicEnvironment::BasicEnvironment(int argc, char* argv[], VerboseLevel verboseLevel, bool printStartupMessage) :
    fVerboseLevel(verboseLevel),
    fSingletonFactory() {
    if (not Initialized()) {
        fgBasicEnvironmentInstance = this;
    } else {
        throw std::logic_error("MACE::Environment::BasicEnvironment: Trying to initialize environment twice");
    }
    if (printStartupMessage) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
}

void BasicEnvironment::PrintStartupMessageSplitLine() const {
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(std::cout, Error, fVerboseLevel)
        << "\n===============================================================================\n"
        << std::endl;
}

void BasicEnvironment::PrintStartupMessageBody(int argc, char* argv[]) const {
    std::error_code cwdError;
    auto cwd = std::filesystem::current_path(cwdError).generic_string();
    if (cwdError) {
        cwd.assign("<Error getting current working directory>");
    }
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(std::cout, Error, fVerboseLevel)
        << " xxxx framework (MACE offline software system) " << MACE_VERSION_STRING << '\n'
        << " Copyright (c) 2020-2022 MACE software working group \n"
        << '\n'
        << " Exe: " << argv[0] << '\n'
        << " CWD: " << cwd << std::endl;
    if (fVerboseLevel >= VerboseLevel::Verbose) {
        std::cout << "\n List of all " << argc << " command line args:\n";
        for (int i = 0; i < argc; ++i) {
            std::cout << "  argv[" << i << "]: " << argv[i] << '\n';
        }
        std::cout << std::flush;
    }
}

} // namespace MACE::Environment
