namespace MACE::Env {

template<class ACLI>
BasicEnv::BasicEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printStartupMessage) :
    EnvBase(),
    FreeSingleton(),
    fVerboseLevel(verboseLevel) {
    // CLI: do parse and get args
    if constexpr (not std::is_same_v<std::remove_cvref_t<ACLI>, internal::NoCLI>) {
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

} // namespace MACE::Env
