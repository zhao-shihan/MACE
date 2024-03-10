#include "MACE/Env/MPIEnv.h++"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace MACE::Env {

MPIEnv::~MPIEnv() {
    // Destructs the local communicator
    auto commNode{fCommNode};
    MPI_Comm_free(&commNode);
    // Wait all processes before finalizing
    MPI_Barrier(MPI_COMM_WORLD);
    // Finalize MPI
    MPI_Finalize();
}

auto MPIEnv::PrintWelcomeMessageBody(int argc, char* argv[]) const -> void {
    BasicEnv::PrintWelcomeMessageBody(argc, argv);
    if (VerboseLevel() >= VL::Error) {
        // MPI library version
        char mpiLibVersion[MPI_MAX_LIBRARY_VERSION_STRING];
        int mpiLibVersionStringLength;
        MPI_Get_library_version(mpiLibVersion,               // version
                                &mpiLibVersionStringLength); // resultlen
        // MPI version at runtime
        std::pair<int, int> mpiRuntimeVersion;
        MPI_Get_version(&mpiRuntimeVersion.first,   // version
                        &mpiRuntimeVersion.second); // subversion
        // Messages
        std::cout << '\n'
                  << " Parallelized with MPI, running " << (Parallel() ? "in parallel" : "sequentially") << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(VerboseLevel(), Verbose, std::cout)
            << " Compiled with MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << ", running with MPI " << mpiRuntimeVersion.first << '.' << mpiRuntimeVersion.second << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(VerboseLevel(), MoreVerbose, std::cout)
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
