namespace MACE::Env {

template<class ACLI>
MPIEnv::MPIEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printStartupMessage) :
    BasicEnv(argc, argv, cli, verboseLevel, false),
    FreeSingleton<MPIEnv>(),
    fWorldCommRank(-1),
    fWorldCommSize(-1),
    fLocalComm(MPI_COMM_NULL),
    fLocalCommRank(-1),
    fLocalCommSize(-1),
    fLocalHostID(-1),
    fHostInfoList() {
    // Initialize MPI and properties of MPI_COMM_WORLD
    InitializeMPI(argc, argv);
    // Disable ROOT implicit multi-threading
    ROOT::DisableImplicitMT();
    // Print startup message
    if (printStartupMessage and AtWorldMaster()) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
    // Update status
    fgInitialized = true;
}

} // namespace MACE::Env
