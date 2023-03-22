#pragma once

#include "MACE/Env/BasicEnv.hxx"

#include "TROOT.h"

#include "mpi.h"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace MACE::Env {

class MPIEnv : public BasicEnv,
               public Memory::PassiveSingleton<MPIEnv> {
public:
    template<class ACLI = internal::NoCLI>
    MPIEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnv();

    using PassiveSingleton<MPIEnv>::Instance;
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

    const auto& HostList() const { return fHostList; }
    auto LocalHostID() const { return fLocalHostID; }
    const auto& Host(int id) const { return fHostList[id]; }
    const auto& LocalHost() const { return Host(fLocalHostID); }
    auto NHost() const { return static_cast<int>(fHostList.size()); }
    auto OnSingleHost() const { return NHost() == 1; }
    auto OnCluster() const { return NHost() > 1; }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPI(int argc, char* argv[]);
    void InitializeHostInfo();

private:
    struct HostInfo {
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
    std::vector<HostInfo> fHostList;

    static bool fgInitialized;
    static bool fgFinalized;
};

} // namespace MACE::Env

#define MACE_MPI_MASTER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                      \
        MACE::Env::MPIEnv::Instance().AtWorldMaster())                             \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                      \
        MACE::Env::MPIEnv::Instance().AtWorldMaster())             \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORKER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                      \
        MACE::Env::MPIEnv::Instance().AtWorldWorker())                             \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                      \
        MACE::Env::MPIEnv::Instance().AtWorldWorker())             \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_MASTER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtLocalMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                           \
        MACE::Env::MPIEnv::Instance().AtLocalMaster())                                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtLocalMaster())                  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_WORKER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtLocalWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                           \
        MACE::Env::MPIEnv::Instance().AtLocalWorker())                                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtLocalWorker())                  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Env/MPIEnv.inl"
