#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Version.h++"

#include <filesystem>
#include <stdexcept>
#include <system_error>

namespace MACE::Env {

void BasicEnv::PrintWelcomeMessageSplitLine() const {
    if (fVerboseLevel >= VL::Error) {
        fmt::print("\n===============================================================================\n");
    }
}

void BasicEnv::PrintWelcomeMessageBody(int argc, char* argv[]) const {
    std::error_code cwdError;
    const auto exe{std::filesystem::path(argv[0]).filename().generic_string()};
    auto cwd{std::filesystem::current_path(cwdError).generic_string()};
    if (cwdError) { cwd = "<Error getting current working directory>"; }
    if (fVerboseLevel >= VL::Error) {
        fmt::print("\n"
                   " MACE offline software system {}\n"
                   " Copyright (c) 2020-2024 MACE working group\n"
                   "\n"
                   " Exe: {}",
                   MACE_VERSION_STRING,
                   exe);
        for (auto i{1}; i < argc; ++i) {
            fmt::print(" {}", argv[i]);
        }
        fmt::print("\n"
                   " CWD: {}\n",
                   cwd);
    }
    if (fVerboseLevel >= VL::Verbose) {
        fmt::print("\n"
                   " List of all {} command line arguments:\n",
                   argc);
        for (int i = 0; i < argc; ++i) {
            fmt::println("  argv[{}]: {}", i, argv[i]);
        }
    }
}

} // namespace MACE::Env
