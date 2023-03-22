#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/FixedString.hxx"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.hxx"
#include "MACE/Utility/MPIUtil/MPICallWithCheckNoExcept.hxx"

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
                                      &fLocalComm);
    // Finalize MPI
    MACE_MPI_CALL_WITH_CHECK_NOEXCEPT(MPI_Finalize)
}

void MPIEnv::PrintStartupMessageBody(int argc, char* argv[]) const {
    BasicEnv::PrintStartupMessageBody(argc, argv);
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
        std::cout << " Size of the MPI world communicator: " << fWorldCommSize << '\n';
        if (OnSingleHost()) {
            std::cout << " Running on " << std::quoted(LocalHost().name) << '\n';
        } else {
            std::cout << " Running on a cluster with " << NHost() << " hosts:\n";
            const auto maxNameWidth = std::ranges::max_element(
                                          std::as_const(fHostList),
                                          [](auto&& host1, auto&& host2) { return host1.name.size() < host2.name.size(); })
                                          ->name.size();
            const auto oldFlags = std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
            const auto oldFill = std::cout.fill(' ');
            for (auto hostID = 0; hostID < NHost(); ++hostID) {
                const auto& host = fHostList[hostID];
                std::cout << "  name: " << std::setw(maxNameWidth) << host.name << "  size: " << host.size << '\n';
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
    // Initialize rank id in the world communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
                             MPI_COMM_WORLD,
                             &fWorldCommRank)
    // Initialize size of the world communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                             MPI_COMM_WORLD,
                             &fWorldCommSize)
    // Initialize informations of all hosts
    InitializeHostInfo();
    // Constructs shared communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_split,
                             MPI_COMM_WORLD,
                             fLocalHostID,
                             0,
                             &fLocalComm)
    // Initialize rank id in the local communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
                             fLocalComm,
                             &fLocalCommRank)
    // Initialize size of the local communicator
    MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                             fLocalComm,
                             &fLocalCommSize)
    // Disable ROOT implicit multi-threading
    if (ROOT::IsImplicitMTEnabled()) {
        ROOT::DisableImplicitMT();
    }
}

void MPIEnv::InitializeHostInfo() {
    using NameFixedString = FixedString<MPI_MAX_PROCESSOR_NAME - 1>;
    // Each rank get its processor name
    NameFixedString hostNameSend;
    int nameLength;
    MACE_MPI_CALL_WITH_CHECK(MPI_Get_processor_name,
                             hostNameSend.Data(),
                             &nameLength)
    // Master collects processor names
    std::vector<NameFixedString> hostNamesRecv;
    if (AtWorldMaster()) { hostNamesRecv.resize(fWorldCommSize); }
    MACE_MPI_CALL_WITH_CHECK(MPI_Gather,
                             hostNameSend.CString(),
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
    std::vector<std::pair<int, NameFixedString>> hostList;
    // Master find all unique processor names and assign host id and count
    if (AtWorldMaster()) {
        hostIDAndCountSend.reserve(fWorldCommSize);
        hostList.reserve(fWorldCommSize);
        // Find unique name and assign host id
        auto currentNodeId = 0;
        auto currentName = &std::as_const(hostNamesRecv).front();
        hostIDAndCountSend.push_back({currentNodeId, -1});
        hostList.emplace_back(-1, *currentName);
        for (auto&& name : std::as_const(hostNamesRecv)) {
            if (name != *currentName) {
                hostList.back().first = std::distance(currentName, &name);
                hostList.emplace_back(-1, name);
                ++currentNodeId;
                currentName = &name;
            }
            hostIDAndCountSend.push_back({currentNodeId, -1});
        }
        hostList.back().first = std::distance(currentName, &std::as_const(hostNamesRecv).back());
        // Assign host count
        for (const int hostCount = hostList.size();
             auto&& [_, hostCountSend] : hostIDAndCountSend) {
            hostCountSend = hostCount;
        }
    }
    // Send host id and count
    MACE_MPI_CALL_WITH_CHECK(MPI_Scatter,
                             std::as_const(hostIDAndCountSend).data(),
                             2,
                             MPI_INT,
                             hostIDAndCountRecv.data(),
                             2,
                             MPI_INT,
                             0,
                             MPI_COMM_WORLD)
    auto&& [hostID, hostCount] = hostIDAndCountRecv;
    // Assign local processor id
    fLocalHostID = hostID;
    // Master send unique host name list
    if (AtWorldWorker()) { hostList.resize(hostCount); }
    MACE_MPI_CALL_WITH_CHECK(MPI_Bcast,
                             hostList.data(),
                             std::span(hostList).size_bytes(),
                             MPI_BYTE,
                             0,
                             MPI_COMM_WORLD)
    // Assign to the list, convert host names to std::string
    fHostList.reserve(hostCount);
    for (auto&& [size, name] : std::as_const(hostList)) {
        fHostList.push_back({size, name});
        fHostList.back().name.shrink_to_fit();
    }
    fHostList.shrink_to_fit();
}

} // namespace MACE::Env
