#pragma once

#include "MACE/Env/BasicEnv.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/FixedString.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"

#include "TROOT.h"

#include "mpi.h"

#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace MACE::Env {

class MPIEnv : public BasicEnv,
               public Memory::PassiveSingleton<MPIEnv> {
public:
    template<typename ACLI = internal::NoCLI>
    MPIEnv(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printWelcomeMessage = true);
    virtual ~MPIEnv();

    using PassiveSingleton<MPIEnv>::Instance;
    static auto Initialized() -> auto { return fgInitialized; }
    static auto Finalized() -> auto { return fgFinalized; }
    static auto Available() -> auto { return Initialized() and not Finalized(); }

    auto CommWorldRank() const -> const auto& { return fCommWorldRank; }
    auto CommWorldSize() const -> const auto& { return fCommWorldSize; }
    auto AtCommWorldMaster() const -> auto { return CommWorldRank() == 0; }
    auto AtCommWorldWorker() const -> auto { return CommWorldRank() > 0; }
    auto Sequential() const -> auto { return CommWorldSize() == 1; }
    auto Parallel() const -> auto { return CommWorldSize() > 1; }

    auto CommShared() const -> const auto& { return fSharedComm; }
    auto CommSharedRank() const -> const auto& { return fSharedCommRank; }
    auto CommSharedSize() const -> const auto& { return fSharedCommSize; }
    auto AtCommSharedMaster() const -> auto { return CommSharedRank() == 0; }
    auto AtCommSharedWorker() const -> auto { return CommSharedRank() > 0; }

    auto NodeList() const -> const auto& { return fCluster.node; }
    auto LocalNodeID() const -> const auto& { return fCluster.local; }
    auto Node(int id) const -> const auto& { return NodeList().at(id); }
    auto LocalNode() const -> const auto& { return Node(LocalNodeID()); }
    auto ClusterSize() const -> int { return NodeList().size(); }
    auto OnSingleNode() const -> auto { return ClusterSize() == 1; }
    auto OnCluster() const -> auto { return ClusterSize() > 1; }

protected:
    auto PrintWelcomeMessageBody(int argc, char* argv[]) const -> void;

private:
    struct NodeInfo {
        int size;
        std::string name;
    };

private:
    const int fCommWorldRank;
    const int fCommWorldSize;

    const struct {
        std::vector<NodeInfo> node;
        int local;
    } fCluster;

    const MPI_Comm fSharedComm;
    const int fSharedCommRank;
    const int fSharedCommSize;

    static bool fgInitialized;
    static bool fgFinalized;
};

} // namespace MACE::Env

#define MACE_MPI_WORLD_MASTER_OUT(out)                           \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldMaster())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORLD_WORKER_OUT(out)                           \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().AtCommWorldWorker())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_MASTER_OUT(out)                          \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_SHARED_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_SHARED_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                             \
        MACE::Env::MPIEnv::Instance().AtCommSharedMaster())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_WORKER_OUT(out)                          \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
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
