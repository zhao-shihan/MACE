namespace MACE::Env {

template<class ACLI>
MPIEnv::MPIEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printWelcomeMessage) :
    BasicEnv(argc, argv, cli, verboseLevel, false),
    PassiveSingleton<MPIEnv>(),
    fCommWorldRank(-1),
    fCommWorldSize(-1),
    fSharedComm(MPI_COMM_NULL),
    fSharedCommRank(-1),
    fSharedCommSize(-1),
    fLocalNodeID(-1),
    fCluster() {
    // Initialize MPI and properties of MPI_COMM_WORLD
    // and disable ROOT implicit multi-threading
    InitializeMPI(argc, argv);
    // Print startup message
    if (printWelcomeMessage and AtCommWorldMaster()) {
        PrintWelcomeMessageSplitLine();
        PrintWelcomeMessageBody(argc, argv);
        PrintWelcomeMessageSplitLine();
    }
    // Update status
    fgInitialized = true;
}

} // namespace MACE::Env
