#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICallNoExcept.hxx"

#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <string_view>

namespace MACE::Environment {

MPIEnvironment::~MPIEnvironment() {
    // Destructs the shared communicator
    MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Comm_free,
                                   &fNodeComm);
    // Finalize MPI
    MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Finalize)
}

void MPIEnvironment::PrintStartupMessageBody(int argc, char* argv[]) const {
    BasicEnvironment::PrintStartupMessageBody(argc, argv);
    if (GetVerboseLevel() >= VerboseLevel::Error) {
        // MPI library version
        char mpiLibVersion[MPI_MAX_LIBRARY_VERSION_STRING];
        int mpiLibVersionStringLength;
        MACE_CHECKED_MPI_CALL(MPI_Get_library_version,
                              mpiLibVersion,
                              &mpiLibVersionStringLength)
        // MPI version at runtime
        std::pair<int, int> mpiRuntimeVersion;
        MACE_CHECKED_MPI_CALL(MPI_Get_version,
                              &mpiRuntimeVersion.first,
                              &mpiRuntimeVersion.second)
        // Messages
        std::cout << '\n'
                  << " Parallelized by MPI, running " << (IsParallel() ? "concurrently" : "sequentially") << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), Verbose, std::cout)
            << " Compiled with MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << ", running with MPI " << mpiRuntimeVersion.first << '.' << mpiRuntimeVersion.second << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), MoreVerbose, std::cout)
            << "--------------------> MPI library information (begin) <--------------------\n"
            << mpiLibVersion << '\n'
            << "-------------------->  MPI library information (end)  <--------------------\n";
        std::cout << " Size of the MPI world communicator: " << fWorldCommSize << '\n';
        if (OnSingleNode()) {
            std::cout << " Running on \"" << NodeName() << "\"\n";
        } else {
            std::cout << " Running on cluster with " << NumberOfNodes() << " nodes:\n";
            for (auto&& [nodeSize, nodeName] : std::as_const(fNodeInfoList)) {
                std::cout << "  Name: " << nodeName << '\t' << " Size: " << nodeSize << '\n';
            }
        }
        std::cout << std::flush;
    }
}

void MPIEnvironment::InitializeMPI(int argc, char* argv[]) {
    // Confirm MPI condition
    int mpiInitialized;
    MACE_CHECKED_MPI_CALL(MPI_Initialized,
                          &mpiInitialized)
    if (mpiInitialized) {
        throw std::logic_error("MACE::Environment::MPIEnvironment: Trying to call MPI_Init twice");
    }
    // Initialize MPI
    MACE_CHECKED_MPI_CALL(MPI_Init,
                          &argc,
                          &argv)
    // Initialize rank id in the world communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_rank,
                          MPI_COMM_WORLD,
                          &fWorldCommRank)
    // Initialize size of the world communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_size,
                          MPI_COMM_WORLD,
                          &fWorldCommSize)
    // Initialize informations of all nodes
    InitializeNodeInfos();
    // Constructs shared communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_split,
                          MPI_COMM_WORLD,
                          fNodeId,
                          0,
                          &fNodeComm)
    // Initialize rank id in the local communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_rank,
                          fNodeComm,
                          &fNodeCommRank)
    // Initialize size of the local communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_size,
                          fNodeComm,
                          &fNodeCommSize)
}

void MPIEnvironment::InitializeNodeInfos() {
    using NameArray = std::array<char, MPI_MAX_PROCESSOR_NAME>;
    // Each rank get its processor name
    NameArray nodeNameSend;
    int nameLength;
    MACE_CHECKED_MPI_CALL(MPI_Get_processor_name, nodeNameSend.data(), &nameLength)
    // Master collects processor names
    std::vector<NameArray> nodeNamesRecv;
    if (IsMaster()) { nodeNamesRecv.resize(fWorldCommSize); }
    MACE_CHECKED_MPI_CALL(MPI_Gather,
                          nodeNameSend.data(),
                          MPI_MAX_PROCESSOR_NAME,
                          MPI_CHAR,
                          nodeNamesRecv.data(),
                          MPI_MAX_PROCESSOR_NAME,
                          MPI_CHAR,
                          0,
                          MPI_COMM_WORLD)
    // Processor name list
    std::vector<std::array<int, 2>> nodeIdAndCountSend;
    std::array<int, 2> nodeIdAndCountRecv;
    std::vector<std::pair<int, NameArray>> nodeInfoList;
    // Master find all unique processor names and assign node id and count
    if (IsMaster()) {
        nodeIdAndCountSend.reserve(fWorldCommSize);
        nodeInfoList.reserve(fWorldCommSize);
        // Find unique name and assign node id
        int currentNodeId = 0;
        auto currentName = nodeNamesRecv.cbegin();
        nodeIdAndCountSend.emplace_back(std::array{currentNodeId, -1});
        nodeInfoList.emplace_back(-1, *currentName);
        for (auto it = std::next(nodeNamesRecv.cbegin()), end = nodeNamesRecv.cend();
             it != end; ++it) {
            if (std::strncmp(currentName->data(), it->data(), MPI_MAX_PROCESSOR_NAME) != 0) {
                nodeInfoList.back().first = static_cast<int>(std::distance(currentName, it));
                nodeInfoList.emplace_back(-1, *it);
                ++currentNodeId;
                currentName = it;
            }
            nodeIdAndCountSend.emplace_back(std::array{currentNodeId, -1});
        }
        nodeInfoList.back().first = static_cast<int>(std::distance(currentName, nodeNamesRecv.cend()));
        // Assign node count
        for (const auto nodeCount = static_cast<int>(nodeInfoList.size());
             auto&& [_, nodeCountSend] : nodeIdAndCountSend) {
            nodeCountSend = nodeCount;
        }
    }
    // Send node id and count
    MACE_CHECKED_MPI_CALL(MPI_Scatter,
                          nodeIdAndCountSend.data(),
                          2,
                          MPI_INT,
                          nodeIdAndCountRecv.data(),
                          2,
                          MPI_INT,
                          0,
                          MPI_COMM_WORLD)
    auto&& [nodeId, nodeCount] = nodeIdAndCountRecv;
    // Master send unique node name list
    if (IsWorker()) { nodeInfoList.resize(nodeCount); }
    MACE_CHECKED_MPI_CALL(MPI_Bcast,
                          nodeInfoList.data(),
                          nodeCount * sizeof(decltype(nodeInfoList)::value_type),
                          MPI_BYTE,
                          0,
                          MPI_COMM_WORLD)
    // Assign to the list, convert node names to std::string
    fNodeInfoList.reserve(nodeCount);
    for (auto&& [nodeSize, nodeName] : std::as_const(nodeInfoList)) {
        auto& nodeInfo = fNodeInfoList.emplace_back(nodeSize, nodeName.data());
        nodeInfo.second.shrink_to_fit();
    }
    fNodeInfoList.shrink_to_fit();
    // Assign local processor information iterator
    fLocalNodeInfo = std::next(fNodeInfoList.cbegin(), nodeId);
    // Assign local processor id
    fNodeId = nodeId;
}

} // namespace MACE::Environment
