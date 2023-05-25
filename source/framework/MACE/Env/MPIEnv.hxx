#pragma once

#include "MACE/Env/BasicEnv.hxx"

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
    MPIEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printWelcomeMessage = true);
    virtual ~MPIEnv();

    using PassiveSingleton<MPIEnv>::Instance;
    static auto Initialized() { return fgInitialized; }
    static auto Finalized() { return fgFinalized; }
    static auto Available() { return Initialized() and not Finalized(); }

    const auto& CommWorldSize() const { return fCommWorldSize; }
    const auto& CommWorldRank() const { return fCommWorldRank; }
    auto AtCommWorldMaster() const { return CommWorldRank() == 0; }
    auto AtCommWorldWorker() const { return CommWorldRank() > 0; }
    auto Sequential() const { return CommWorldSize() == 1; }
    auto Parallel() const { return CommWorldSize() > 1; }

    const auto& CommShared() const { return fSharedComm; }
    const auto& CommSharedSize() const { return fSharedCommSize; }
    const auto& CommSharedRank() const { return fSharedCommRank; }
    auto AtCommSharedMaster() const { return CommSharedRank() == 0; }
    auto AtCommSharedWorker() const { return CommSharedRank() > 0; }

    const auto& NodeList() const { return fCluster; }
    auto LocalNodeID() const { return fLocalNodeID; }
    const auto& Node(int id) const { return fCluster[id]; }
    const auto& LocalNode() const { return Node(fLocalNodeID); }
    auto ClusterSize() const { return static_cast<int>(fCluster.size()); }
    auto OnSingleNode() const { return ClusterSize() == 1; }
    auto OnCluster() const { return ClusterSize() > 1; }

protected:
    void PrintWelcomeMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPI(int argc, char* argv[]);
    void InitializeNodeInfo();

private:
    struct NodeInfo {
        int size;
        std::string name;
    };

private:
    int fCommWorldRank;
    int fCommWorldSize;

    MPI_Comm fSharedComm;
    int fSharedCommRank;
    int fSharedCommSize;

    int fLocalNodeID;
    std::vector<NodeInfo> fCluster;

    static bool fgInitialized;
    static bool fgFinalized;
};

} // namespace MACE::Env

#define MACE_MPI_WORLD_MASTER_OUT(out)                                  \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORLD_WORKER_OUT(out)                                  \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_MASTER_OUT(out)                                 \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_SHARED_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_SHARED_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_WORKER_OUT(out)                                 \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Env::MPIEnv::Available() or                           \
        MACE::Env::MPIEnv::Instance().AtCommSharedWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_SHARED_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedWorker())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_SHARED_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedWorker())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Env/MPIEnv.inl"
