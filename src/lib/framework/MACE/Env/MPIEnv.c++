#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheckNoExcept.h++"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace MACE::Env {

bool MPIEnv::fgInitialized = false;
bool MPIEnv::fgFinalized = false;

MPIEnv::~MPIEnv() {
    // Update status
    fgFinalized = true;
    // Destructs the local communicator
    auto sharedComm = fSharedComm;
    MACE_MPI_CALL_WITH_CHECK_NOEXCEPT(MPI_Comm_free,
                                      &sharedComm);
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
            const auto maxNameWidth = std::ranges::max_element(NodeList(),
                                                               [](auto&& node1, auto&& node2) { return node1.name.size() < node2.name.size(); })
                                          ->name.size();
            const auto oldFlags = std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
            const auto oldFill = std::cout.fill(' ');
            for (auto nodeID = 0; nodeID < ClusterSize(); ++nodeID) {
                const auto& node = Node(nodeID);
                std::cout << "  name: " << std::setw(maxNameWidth) << node.name << "  size: " << node.size << '\n';
            }
            std::cout << std::setfill(oldFill)
                      << std::setiosflags(oldFlags);
        }
    }
}

} // namespace MACE::Env
