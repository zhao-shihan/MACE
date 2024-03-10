namespace MACE::Env {

template<typename ACLI>
BasicEnv::BasicEnv(int argc, char* argv[], ACLI&& cli, VL verboseLevel, bool printWelcomeMessage) :
    EnvBase{},
    PassiveSingleton{},
    fArgc{argc},
    fArgv{argv},
    fVerboseLevel{verboseLevel} {
    // CLI: do parse and get args
    if constexpr (not std::is_same_v<std::decay_t<ACLI>, internal::NoCLI>) {
        // Parse
        cli.ParseArgs(argc, argv);
        // Get args
        fVerboseLevel = cli.VerboseLevel().value_or(verboseLevel);
    }
    // Print startup message after parse
    if (printWelcomeMessage) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
}

} // namespace MACE::Env
