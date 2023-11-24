namespace MACE::Env {

template<typename ACLI>
BasicEnv::BasicEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printWelcomeMessage) :
    EnvBase(),
    PassiveSingleton(),
    fVerboseLevel(verboseLevel) {
    // CLI: do parse and get args
    if constexpr (not std::is_same_v<std::decay_t<ACLI>, internal::NoCLI>) {
        // Parse
        cli.ParseArgs(argc, argv);
        // Get args
        fVerboseLevel = cli.GetVerboseLevel().value_or(verboseLevel);
    }
    // Print startup message after parse
    if (printWelcomeMessage) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
}

} // namespace MACE::Env
