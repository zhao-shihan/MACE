#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/FixedString.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheckNoExcept.h++"

#include "TROOT.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <span>
#include <utility>

namespace MACE::Env {

bool MPIEnv::fgInitialized = false;
bool MPIEnv::fgFinalized = false;

MPIEnv::~MPIEnv() {
    // Update status
    fgFinalized = true;
    // Destructs the local communicator
    MACE_MPI_CALL_WITH_CHECK_NOEXCEPT(MPI_Comm_free,
                                      &fSharedComm);
    // Finalize MPI
    MACE_MPI_CALL_WITH_CHECK_NOEXCEPT(MPI_Finalize)
}

void MPIEnv::PrintWelcomeMessageBody(int argc, char* argv[]) const {
    BasicEnv::PrintWelcomeMessageBody(argc, argv);
    if (GetVerboseLevel() >= VerboseLevel::Error) {
        // MPI library version
        char mpiLibVersion[MPI_MAX_LIBRARY_VERSION_STRING];
        int mpiLibVersionStringLength;
        MACE_MPI_CALL_WITH_CHECK(MPI_Get_library_version,
                                 mpiLibVersion,
                                 &mpiLibVersionStringLength)
        // MPI version at runtime
        std::pair<int, int> mpiRuntimeVersion;
        MACE_MPI_CALL_WITH_CHECK(MPI_Get_version,
                                 &mpiRuntimeVersion.first,
                                 &mpiRuntimeVersion.second)
        // Messages
        std::cout << '\n'
                  << " Parallelized by MPI, running " << (Parallel() ? "in parallel" : "sequentially") << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), Verbose, std::cout)
            << " Compiled with MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << ", running with MPI " << mpiRuntimeVersion.first << '.' << mpiRuntimeVersion.second << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), MoreVerbose, std::cout)
            << "--------------------> MPI library information (begin) <--------------------\n"
            << mpiLibVersion << '\n'
            << "-------------------->  MPI library information (end)  <--------------------\n";
        std::cout << " Size of the MPI world communicator: " << fCommWorldSize << '\n';
        if (OnSingleNode()) {
            std::cout << " Running on " << std::quoted(LocalNode().name) << '\n';
        } else {
            std::cout << " Running on a cluster with " << ClusterSize() << " nodes:\n";
            const auto maxNameWidth = std::ranges::max_element(
                                          std::as_const(fCluster),
                                          [](auto&& node1, auto&& node2) { return node1.name.size() < node2.name.size(); })
                                          ->name.size();
            const auto oldFlags = std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
            const auto oldFill = std::cout.fill(' ');
            for (auto nodeID = 0; nodeID < ClusterSize(); ++nodeID) {
                const auto& node = fCluster[nodeID];
                std::cout << "  name: " << std::setw(maxNameWidth) << node.name << "  size: " << node.size << '\n';
            }
            std::cout << std::setfill(oldFill)
                      << std::setiosflags(oldFlags);
        }
    }
}

void MPIEnv::InitializeMPI(int argc, char* argv[]) {
    // Confirm MPI condition
    int mpiInitialized;
    MACE_MPI_CALL_WITH_CHECK(MPI_Initialized,
                             &mpiInitialized)
    if (mpiInitialized) {
        throw std::logic_error("MACE::Env::MPIEnv: Trying to call MPI_Init twice");
    }
    // Initialize MPI
    MACE_MPI_CALL_WITH_CHECK(MPI_Init,
                             &argc,
                             &argv)
    // Initialize rank ID in the world communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
                             MPI_COMM_WORLD,
                             &fCommWorldRank)
    // Initialize size of the world communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                             MPI_COMM_WORLD,
                             &fCommWorldSize)
    // Initialize informations of all nodes
    InitializeNodeInfo();
    // Constructs shared communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_split,
                             MPI_COMM_WORLD,
                             fLocalNodeID,
                             0,
                             &fSharedComm)
    // Initialize rank ID in the local communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
                             fSharedComm,
                             &fSharedCommRank)
    // Initialize size of the local communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                             fSharedComm,
                             &fSharedCommSize)
    // Disable ROOT implicit multi-threading
    if (ROOT::IsImplicitMTEnabled()) {
        ROOT::DisableImplicitMT();
    }
}

void MPIEnv::InitializeNodeInfo() {
    using NameFixedString = FixedString<MPI_MAX_PROCESSOR_NAME>;
    // Each rank get its processor name
    NameFixedString nodeNameSend;
    int nameLength;
    MACE_MPI_CALL_WITH_CHECK(MPI_Get_processor_name,
                             nodeNameSend.Data(),
                             &nameLength)
    // Master collects processor names
    std::vector<NameFixedString> nodeNamesRecv;
    if (AtCommWorldMaster()) { nodeNamesRecv.resize(fCommWorldSize); }
    MACE_MPI_CALL_WITH_CHECK(MPI_Gather,
                             nodeNameSend.CString(),
                             NameFixedString::Occupation(),
                             MPI_CHAR,
                             nodeNamesRecv.data(),
                             NameFixedString::Occupation(),
                             MPI_CHAR,
                             0,
                             MPI_COMM_WORLD)
    // Processor name list
    std::vector<stdx::array2i> nodeIDAndCountSend;
    stdx::array2i nodeIDAndCountRecv;
    struct NodeInfoForMPI {
        int size;
        NameFixedString name;
    };
    std::vector<NodeInfoForMPI> nodeList;
    // Master find all unique processor names and assign node ID and count
    if (AtCommWorldMaster()) {
        nodeIDAndCountSend.reserve(fCommWorldSize);
        nodeList.reserve(fCommWorldSize);
        // Find unique name and assign node ID
        auto currentNodeID = 0;
        auto currentNodeName = std::as_const(nodeNamesRecv).data();
        for (auto&& name : std::as_const(nodeNamesRecv)) {
            if (name != *currentNodeName) {
                nodeList.push_back({static_cast<int>(std::distance(currentNodeName, &name)),
                                    *currentNodeName});
                ++currentNodeID;
                currentNodeName = &name;
            }
            nodeIDAndCountSend.push_back({currentNodeID, -1});
        }
        nodeList.push_back({static_cast<int>(std::distance(currentNodeName, std::to_address(nodeNamesRecv.cend()))),
                            *currentNodeName});
        // Assign node count
        for (const int nodeCount = nodeList.size();
             auto&& [_, nodeCountSend] : nodeIDAndCountSend) {
            nodeCountSend = nodeCount;
        }
    }
    // Send node ID and count
    MACE_MPI_CALL_WITH_CHECK(MPI_Scatter,
                             std::as_const(nodeIDAndCountSend).data(),
                             1,
                             MPI_2INT,
                             nodeIDAndCountRecv.data(),
                             1,
                             MPI_2INT,
                             0,
                             MPI_COMM_WORLD)
    auto&& [nodeID, nodeCount] = nodeIDAndCountRecv;
    // Assign local processor ID
    fLocalNodeID = nodeID;
    // Master send unique node name list
    if (AtCommWorldWorker()) { nodeList.resize(nodeCount); }
    constexpr int blockLengthOfNodeInfoForMPI[] = {1, NameFixedString::Occupation()};
    constexpr MPI_Aint displacementOfNodeInfoForMPI[] = {offsetof(NodeInfoForMPI, size), offsetof(NodeInfoForMPI, name)};
    constexpr MPI_Datatype typeOfNodeInfoForMPI[] = {MPI_INT, MPI_CHAR};
    MPI_Datatype nodeInfoForMPI;
    MACE_MPI_CALL_WITH_CHECK(MPI_Type_create_struct,
                             2,
                             blockLengthOfNodeInfoForMPI,
                             displacementOfNodeInfoForMPI,
                             typeOfNodeInfoForMPI,
                             &nodeInfoForMPI)
    MACE_MPI_CALL_WITH_CHECK(MPI_Type_commit,
                             &nodeInfoForMPI)
    MACE_MPI_CALL_WITH_CHECK(MPI_Bcast,
                             nodeList.data(),
                             nodeList.size(),
                             nodeInfoForMPI,
                             0,
                             MPI_COMM_WORLD)
    MACE_MPI_CALL_WITH_CHECK(MPI_Type_free,
                             &nodeInfoForMPI)
    // Assign to the list, convert node names to std::string
    fCluster.reserve(nodeCount);
    for (auto&& [size, name] : std::as_const(nodeList)) {
        fCluster.push_back({size, name});
        fCluster.back().name.shrink_to_fit();
    }
    fCluster.shrink_to_fit();
}

} // namespace MACE::Env
