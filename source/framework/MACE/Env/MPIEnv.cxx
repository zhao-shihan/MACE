#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICallNoExcept.hxx"
#include "MACE/stdx/array_alias.hxx"

#include <algorithm>
#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <span>
#include <string_view>

namespace MACE::Env {

bool MPIEnv::fgInitialized = false;
bool MPIEnv::fgFinalized = false;

MPIEnv::~MPIEnv() {
    // Update status
    fgFinalized = true;
    // Destructs the local communicator
    MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Comm_free,
                                   &fLocalComm);
    // Finalize MPI
    MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Finalize)
}

void MPIEnv::PrintStartupMessageBody(int argc, char* argv[]) const {
    BasicEnv::PrintStartupMessageBody(argc, argv);
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
                  << " Parallelized by MPI, running " << (Parallel() ? "in parallel" : "sequentially") << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), Verbose, std::cout)
            << " Compiled with MPI " << MPI_VERSION << '.' << MPI_SUBVERSION << ", running with MPI " << mpiRuntimeVersion.first << '.' << mpiRuntimeVersion.second << '\n';
        MACE_VERBOSE_LEVEL_CONTROLLED_OUT(GetVerboseLevel(), MoreVerbose, std::cout)
            << "--------------------> MPI library information (begin) <--------------------\n"
            << mpiLibVersion << '\n'
            << "-------------------->  MPI library information (end)  <--------------------\n";
        std::cout << " Size of the MPI world communicator: " << fWorldCommSize << '\n';
        if (OnSingleHost()) {
            std::cout << " Running on \"" << LocalHostName() << "\"\n";
        } else {
            std::cout << " Running on cluster with " << HostNum() << " hosts:\n";
            const auto maxNameWidth = std::ranges::max_element(
                                          std::as_const(fHostInfoList),
                                          [](auto&& a, auto&& b) { return a.name.size() < b.name.size(); })
                                          ->name.size();
            const auto oldFlags = std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
            const auto oldFill = std::cout.fill(' ');
            for (auto&& [hostSize, hostName] : std::as_const(fHostInfoList)) {
                std::cout << "  Name: " << std::setw(maxNameWidth) << hostName << "  Size: " << hostSize << '\n';
            }
            std::cout << std::setfill(oldFill)
                      << std::setiosflags(oldFlags);
        }
    }
}

void MPIEnv::InitializeMPI(int argc, char* argv[]) {
    // Confirm MPI condition
    int mpiInitialized;
    MACE_CHECKED_MPI_CALL(MPI_Initialized,
                          &mpiInitialized)
    if (mpiInitialized) {
        throw std::logic_error("MACE::Env::MPIEnv: Trying to call MPI_Init twice");
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
    // Initialize informations of all hosts
    InitializeHostInfos();
    // Constructs shared communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_split,
                          MPI_COMM_WORLD,
                          fLocalHostID,
                          0,
                          &fLocalComm)
    // Initialize rank id in the local communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_rank,
                          fLocalComm,
                          &fLocalCommRank)
    // Initialize size of the local communicator
    MACE_CHECKED_MPI_CALL(MPI_Comm_size,
                          fLocalComm,
                          &fLocalCommSize)
}

void MPIEnv::InitializeHostInfos() {
    using NameArray = std::array<char, MPI_MAX_PROCESSOR_NAME>;
    // Each rank get its processor name
    NameArray hostNameSend;
    int nameLength;
    MACE_CHECKED_MPI_CALL(MPI_Get_processor_name,
                          hostNameSend.data(),
                          &nameLength)
    // Master collects processor names
    std::vector<NameArray> hostNamesRecv;
    if (AtWorldMaster()) { hostNamesRecv.resize(fWorldCommSize); }
    MACE_CHECKED_MPI_CALL(MPI_Gather,
                          hostNameSend.data(),
                          MPI_MAX_PROCESSOR_NAME,
                          MPI_CHAR,
                          hostNamesRecv.data(),
                          MPI_MAX_PROCESSOR_NAME,
                          MPI_CHAR,
                          0,
                          MPI_COMM_WORLD)
    // Processor name list
    std::vector<stdx::array2i> hostIDAndCountSend;
    stdx::array2i hostIDAndCountRecv;
    std::vector<std::pair<int, NameArray>> hostInfoList;
    // Master find all unique processor names and assign host id and count
    if (AtWorldMaster()) {
        hostIDAndCountSend.reserve(fWorldCommSize);
        hostInfoList.reserve(fWorldCommSize);
        // Find unique name and assign host id
        int currentNodeId = 0;
        auto currentName = hostNamesRecv.cbegin();
        hostIDAndCountSend.emplace_back(std::array{currentNodeId, -1});
        hostInfoList.emplace_back(-1, *currentName);
        for (auto it = std::next(hostNamesRecv.cbegin()), end = hostNamesRecv.cend();
             it != end; ++it) {
            if (std::strncmp(currentName->data(), it->data(), MPI_MAX_PROCESSOR_NAME) != 0) {
                hostInfoList.back().first = std::distance(currentName, it);
                hostInfoList.emplace_back(-1, *it);
                ++currentNodeId;
                currentName = it;
            }
            hostIDAndCountSend.emplace_back(std::array{currentNodeId, -1});
        }
        hostInfoList.back().first = std::distance(currentName, hostNamesRecv.cend());
        // Assign host count
        for (const int hostCount = hostInfoList.size();
             auto&& [_, hostCountSend] : hostIDAndCountSend) {
            hostCountSend = hostCount;
        }
    }
    // Send host id and count
    MACE_CHECKED_MPI_CALL(MPI_Scatter,
                          hostIDAndCountSend.data(),
                          2,
                          MPI_INT,
                          hostIDAndCountRecv.data(),
                          2,
                          MPI_INT,
                          0,
                          MPI_COMM_WORLD)
    auto&& [hostID, hostCount] = hostIDAndCountRecv;
    // Master send unique host name list
    if (AtWorldWorker()) { hostInfoList.resize(hostCount); }
    MACE_CHECKED_MPI_CALL(MPI_Bcast,
                          hostInfoList.data(),
                          std::span(hostInfoList).size_bytes(),
                          MPI_BYTE,
                          0,
                          MPI_COMM_WORLD)
    // Assign to the list, convert host names to std::string
    fHostInfoList.reserve(hostCount);
    for (auto&& [hostSize, hostName] : std::as_const(hostInfoList)) {
        auto& hostInfo = fHostInfoList.emplace_back(Host{hostSize, hostName.data()});
        hostInfo.name.shrink_to_fit();
    }
    fHostInfoList.shrink_to_fit();
    // Assign local processor id
    fLocalHostID = hostID;
}

} // namespace MACE::Env
