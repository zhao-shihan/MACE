#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"

#include "mpi.h"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace MACE::Environment {

class MPIEnvironment : public BasicEnvironment,
                       public Memory::FreeSingleton<MPIEnvironment> {
public:
    template<class ACLI = internal::NoCLI>
    MPIEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnvironment();

    using FreeSingleton<MPIEnvironment>::Instance;
    static auto Initialized() { return fgInitialized; }
    static auto Finalized() { return fgFinalized; }
    static auto Available() { return Initialized() and not Finalized(); }

    const auto& WorldCommSize() const { return fWorldCommSize; }
    const auto& WorldCommRank() const { return fWorldCommRank; }
    auto AtWorldMaster() const { return WorldCommRank() == 0; }
    auto AtWorldWorker() const { return WorldCommRank() > 0; }
    auto Sequential() const { return WorldCommSize() == 1; }
    auto Parallel() const { return WorldCommSize() > 1; }

    const auto& LocalComm() const { return fLocalComm; }
    const auto& LocalCommSize() const { return fLocalCommSize; }
    const auto& LocalCommRank() const { return fLocalCommRank; }
    auto AtLocalMaster() const { return LocalCommRank() == 0; }
    auto AtLocalWorker() const { return LocalCommRank() > 0; }

    auto NumberOfHosts() const { return fHostInfoList.size(); }
    auto OnSingleHost() const { return NumberOfHosts() == 1; }
    auto OnCluster() const { return NumberOfHosts() > 1; }
    const auto& HostInfoList() const { return fHostInfoList; }
    const auto& HostInfo(int id) const { return fHostInfoList[id]; }
    const auto& HostSize(int id) const { return HostInfo(id).size; }
    const auto& HostName(int id) const { return HostInfo(id).name; }
    auto LocalHostID() const { return fLocalHostID; }
    const auto& LocalHostInfo() const { return HostInfo(fLocalHostID); }
    const auto& LocalHostSize() const { return HostSize(fLocalHostID); }
    const auto& LocalHostName() const { return HostName(fLocalHostID); }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPI(int argc, char* argv[]);
    void InitializeHostInfos();

private:
    struct Host {
        int size;
        std::string name;
    };

private:
    int fWorldCommRank;
    int fWorldCommSize;

    MPI_Comm fLocalComm;
    int fLocalCommRank;
    int fLocalCommSize;

    int fLocalHostID;
    std::vector<Host> fHostInfoList;

    static bool fgInitialized;
    static bool fgFinalized;
};

} // namespace MACE::Environment

#define MACE_MPI_MASTER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                      \
        MACE::Environment::MPIEnvironment::Instance().AtWorldMaster())             \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_MASTER_OUT(Threshold, out)     \
    if (not MACE::Environment::MPIEnvironment::Available() or          \
        MACE::Environment::MPIEnvironment::Instance().AtWorldMaster()) \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORKER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                      \
        MACE::Environment::MPIEnvironment::Instance().AtWorldWorker())             \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORKER_OUT(Threshold, out)     \
    if (not MACE::Environment::MPIEnvironment::Available() or          \
        MACE::Environment::MPIEnvironment::Instance().AtWorldWorker()) \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_MASTER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalMaster())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_MASTER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalMaster())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_WORKER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalWorker())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_WORKER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().AtLocalWorker())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Environment/MPIEnvironment.inl"
