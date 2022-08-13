namespace MACE::Environment {

template<class ACLI>
MPIEnvironment::MPIEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printStartupMessage) :
    BasicEnvironment(argc, argv, cli, verboseLevel, false),
    FreeSingleton<MPIEnvironment>(),
    fWorldRank(-1),
    fWorldSize(-1),
    fNodeInfoList(),
    fNodeId(-1),
    fNodeComm(MPI_COMM_NULL),
    fNodeRank(-1),
    fNodeSize(-1) {
    // Initialize MPI and properties of MPI_COMM_WORLD
    InitializeMPI(argc, argv);
    // Print startup message
    if (printStartupMessage and IsMaster()) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
    // Update status
    fgInitialized = true;
}

} // namespace MACE::Environment
