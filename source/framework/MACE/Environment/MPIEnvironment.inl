namespace MACE::Environment {

template<class ACLI>
MPIEnvironment::MPIEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel, bool printStartupMessage) :
    BasicEnvironment(argc, argv, cli, verboseLevel, false),
    fWorldCommRank(-1),
    fWorldCommSize(-1),
    fNodeInfoList(),
    fLocalNodeInfo(fNodeInfoList.cend()),
    fNodeId(-1),
    fNodeComm(MPI_COMM_NULL),
    fNodeCommRank(-1),
    fNodeCommSize(-1) {
    // Initialize MPI and properties of MPI_COMM_WORLD
    InitializeMPI(argc, argv);
    // Print startup message
    if (printStartupMessage and IsMaster()) {
        PrintStartupMessageSplitLine();
        PrintStartupMessageBody(argc, argv);
        PrintStartupMessageSplitLine();
    }
}

} // namespace MACE::Environment
