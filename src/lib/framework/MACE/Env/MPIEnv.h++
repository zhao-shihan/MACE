#pragma once

#include "MACE/Env/BasicEnv.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/FixedString.h++"

#include "TROOT.h"

#include "mpi.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <map>
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
    MPIEnv(int argc, char* argv[], ACLI&& cli, VL verboseLevel = VL::Warning, bool printWelcomeMessage = true);
    virtual ~MPIEnv();

    using PassiveSingleton<MPIEnv>::Instance;
    using PassiveSingleton<MPIEnv>::Available;
    using PassiveSingleton<MPIEnv>::Expired;
    using PassiveSingleton<MPIEnv>::Instantiated;
    static auto Initialized() -> auto { return Instantiated(); }
    static auto Finalized() -> auto { return Expired(); }

    auto MPIThreadSupport() const -> const auto& { return fMPIThreadSupport; }

    auto CommWorldRank() const -> const auto& { return fCommWorldRank; }
    auto CommWorldSize() const -> const auto& { return fCommWorldSize; }
    auto OnCommWorldMaster() const -> auto { return CommWorldRank() == 0; }
    auto OnCommWorldWorker() const -> auto { return CommWorldRank() != 0; }
    auto Sequential() const -> auto { return CommWorldSize() == 1; }
    auto Parallel() const -> auto { return CommWorldSize() != 1; }

    auto CommNode() const -> const auto& { return fCommNode; }
    auto CommNodeRank() const -> const auto& { return fCommNodeRank; }
    auto CommNodeSize() const -> const auto& { return fCommNodeSize; }
    auto OnCommNodeMaster() const -> auto { return CommNodeRank() == 0; }
    auto OnCommNodeWorker() const -> auto { return CommNodeRank() != 0; }

    auto NodeList() const -> const auto& { return fCluster.node; }
    auto LocalNodeID() const -> const auto& { return fCluster.local; }
    auto Node(int id) const -> const auto& { return NodeList().at(id); }
    auto LocalNode() const -> const auto& { return Node(LocalNodeID()); }
    auto ClusterSize() const -> int { return NodeList().size(); }
    auto OnSingleNode() const -> auto { return ClusterSize() == 1; }
    auto OnCluster() const -> auto { return ClusterSize() != 1; }

protected:
    auto PrintWelcomeMessageBody(int argc, char* argv[]) const -> void;

private:
    struct NodeInfo {
        int size;
        std::string name;
    };

private:
    const int fMPIThreadSupport;

    const int fCommWorldRank;
    const int fCommWorldSize;

    const struct {
        std::vector<NodeInfo> node;
        int local;
    } fCluster;

    const MPI_Comm fCommNode;
    const int fCommNodeRank;
    const int fCommNodeSize;
};

} // namespace MACE::Env

#define MACE_MPI_WORLD_MASTER_OUT(out)                           \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().OnCommWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().OnCommWorldMaster())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().OnCommWorldMaster())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORLD_WORKER_OUT(out)                           \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().OnCommWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORLD_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                            \
        MACE::Env::MPIEnv::Instance().OnCommWorldWorker())                               \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORLD_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                            \
        MACE::Env::MPIEnv::Instance().OnCommWorldWorker())               \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_MASTER_OUT(out)                          \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().OnCommNodeMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_SHARED_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                             \
        MACE::Env::MPIEnv::Instance().OnCommNodeMaster())                                 \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_SHARED_MASTER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                             \
        MACE::Env::MPIEnv::Instance().OnCommNodeMaster())                 \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_SHARED_WORKER_OUT(out)                          \
    static_assert(std::derived_from<std::decay_t<decltype(out)>, \
                                    std::ostream>);              \
    if (not MACE::Env::MPIEnv::Available() or                    \
        MACE::Env::MPIEnv::Instance().OnCommNodeWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_SHARED_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                                             \
        MACE::Env::MPIEnv::Instance().OnCommNodeWorker())                                 \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_SHARED_WORKER_OUT(Threshold, out) \
    if (not MACE::Env::MPIEnv::Available() or                             \
        MACE::Env::MPIEnv::Instance().OnCommNodeWorker())                 \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Env/MPIEnv.inl"
