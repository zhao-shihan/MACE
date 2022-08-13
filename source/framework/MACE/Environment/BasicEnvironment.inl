namespace MACE::Environment {

template<class ACLI>
BasicEnvironment::BasicEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printStartupMessage) :
    EnvironmentBase(),
    FreeSingleton<BasicEnvironment>(),
    fVerboseLevel(verboseLevel) {
    // CLI: do parse and get args
    if constexpr (not std::is_same_v<std::remove_cvref_t<ACLI>, Internal::NoCLI>) {
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

} // namespace MACE::Environment
