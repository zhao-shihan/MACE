#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/CLI/BasicCLI.hxx"
#include "MACE/Version.hxx"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <system_error>

namespace MACE::Env {

void BasicEnv::PrintStartupMessageSplitLine() const {
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(fVerboseLevel, Error, std::cout)
        << "\n===============================================================================\n"
        << std::endl;
}

void BasicEnv::PrintStartupMessageBody(int argc, char* argv[]) const {
    std::error_code cwdError;
    const auto exe = std::filesystem::path(argv[0]).filename().generic_string();
    auto cwd = std::filesystem::current_path(cwdError).generic_string();
    if (cwdError) { cwd = "<Error getting current working directory>"; }
    if (fVerboseLevel >= VerboseLevel::Error) {
        std::cout << " MACE offline software system " << MACE_VERSION_STRING << '\n'
                  << " Copyright (c) 2020-2023 MACE working group \n"
                  << '\n'
                  << " Exe: " << exe;
        for (int i = 1; i < argc; ++i) {
            std::cout << ' ' << argv[i];
        }
        std::cout << '\n'
                  << " CWD: " << cwd << '\n';
    }
    if (fVerboseLevel >= VerboseLevel::Verbose) {
        std::cout << "\n List of all " << argc << " command line arguments:\n";
        for (int i = 0; i < argc; ++i) {
            std::cout << "  argv[" << i << "]: " << argv[i] << '\n';
        }
    }
}

} // namespace MACE::Env
