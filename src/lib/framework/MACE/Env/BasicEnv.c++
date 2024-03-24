#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Version.h++"

#include "fmt/format.h"

#include <filesystem>
#include <system_error>
#include <typeinfo>

namespace MACE::Env {

BasicEnv::BasicEnv(int argc, char* argv[],
                   std::optional<std::reference_wrapper<CLI::BasicCLI>> cli,
                   enum VerboseLevel verboseLevel,
                   bool printWelcomeMessage) :
    EnvBase{},
    PassiveSingleton{},
    fArgc{argc},
    fArgv{argv},
    fVerboseLevel{verboseLevel} {
    // CLI: do parse and get args
    if (cli) {
        cli->get().ParseArgs(argc, argv);
        fVerboseLevel = cli->get().VerboseLevel().value_or(verboseLevel);
    }
    // Print startup message after parse
    if (printWelcomeMessage) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
}

auto BasicEnv::PrintWelcomeMessageSplitLine() const -> void {
    if (Env::VerboseLevelReach<'E'>()) {
        fmt::print("\n===============================================================================\n");
    }
}

auto BasicEnv::PrintWelcomeMessageBody(int argc, char* argv[]) const -> void {
    std::error_code cwdError;
    const auto exe{std::filesystem::path(argv[0]).filename().generic_string()};
    auto cwd{std::filesystem::current_path(cwdError).generic_string()};
    if (cwdError) { cwd = "<Error getting current working directory>"; }
    if (Env::VerboseLevelReach<'E'>()) {
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
    if (Env::VerboseLevelReach<'I'>()) {
        fmt::print("\n"
                   " List of all {} command line arguments:\n",
                   argc);
        for (int i{}; i < argc; ++i) {
            fmt::println("  argv[{}]: {}", i, argv[i]);
        }
    }
}

} // namespace MACE::Env
