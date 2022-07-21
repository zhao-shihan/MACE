#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Version.hxx"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <system_error>

#if MACE_SIGNAL_HANDLER
    #include "MACE/Environment/detail/SignalHandler.hxx"
#endif

namespace MACE::Environment {

ObserverPtr<BasicEnvironment> BasicEnvironment::fgBasicEnvironmentInstance = nullptr;
bool BasicEnvironment::fgBasicEnvironmentFinalized = false;

BasicEnvironment::BasicEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                                   VerboseLevel verboseLevel, bool printStartupMessage) :
    fVerboseLevel(verboseLevel),
#if MACE_SIGNAL_HANDLER
    fSignalHandler(std::make_unique<Detail::SignalHandler>()),
#else
    fSignalHandler(nullptr),
#endif
    fSingletonFactory() {
    // Check double construction
    if (Initialized()) {
        throw std::logic_error("MACE::Environment::BasicEnvironment: Trying to initialize environment twice");
    }
    // CLI: do parse and get args
    if (optCLI.has_value()) {
        auto& cli = optCLI->get();
        // Parse
        DoCLIParse(argc, argv, cli);
        // Get args
        fVerboseLevel = cli.GetVerboseLevel();
    }
    // Print startup message after parse
    if (printStartupMessage) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
    // Set instance pointer
    fgBasicEnvironmentInstance = this;
}

BasicEnvironment::~BasicEnvironment() {
    fgBasicEnvironmentFinalized = true;
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
        << " CWD: " << cwd << std::endl;
    if (fVerboseLevel >= VerboseLevel::Verbose) {
        std::cout << "\n List of all " << argc << " command line args:\n";
        for (int i = 0; i < argc; ++i) {
            std::cout << "  argv[" << i << "]: " << argv[i] << '\n';
        }
        std::cout << std::flush;
    }
}

void BasicEnvironment::DoCLIParse(int argc, const char* const argv[], CLI::BasicCLI& cli) {
    try {
        cli.parse_args(argc, argv);
    } catch (const std::runtime_error& exception) {
        std::cerr << exception.what() << '\n'
                  << "Try: " << argv[0] << " --help" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

} // namespace MACE::Environment
