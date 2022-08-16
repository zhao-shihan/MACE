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

    const auto& GetWorldRank() const { return fWorldRank; }
    const auto& GetWorldSize() const { return fWorldSize; }
    auto IsMaster() const { return GetWorldRank() == 0; }
    auto IsWorker() const { return GetWorldRank() > 0; }
    auto IsSequential() const { return GetWorldSize() == 1; }
    auto IsParallel() const { return GetWorldSize() > 1; }

    const auto& GetNodeInfoList() const { return fNodeInfoList; }
    const auto& GetNodeInfo(std::size_t id) const { return fNodeInfoList[id]; }
    const auto& GetNodeSize(std::size_t id) const { return GetNodeInfo(id).first; }
    const auto& GetNodeName(std::size_t id) const { return GetNodeInfo(id).second; }
    const auto& GetNodeInfo() const { return GetNodeInfo(fNodeId); }
    const auto& GetNodeName() const { return GetNodeName(fNodeId); }
    const auto& GetNodeId() const { return fNodeId; }
    auto GetNumberOfNodes() const { return GetNodeInfoList().size(); }
    auto OnSingleNode() const { return GetNumberOfNodes() == 1; }
    auto OnCluster() const { return GetNumberOfNodes() > 1; }

    const auto& GetNodeComm() const { return fNodeComm; }
    const auto& GetNodeRank() const { return fNodeRank; }
    const auto& GetNodeSize() const { return fNodeSize; }
    auto IsNodeMaster() const { return GetNodeRank() == 0; }
    auto IsNodeWorker() const { return GetNodeRank() > 0; }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPI(int argc, char* argv[]);
    void InitializeNodeInfos();

private:
    int fWorldRank;
    int fWorldSize;

    std::vector<std::pair<int, std::string>> fNodeInfoList;
    int fNodeId;

    MPI_Comm fNodeComm;
    int fNodeRank;
    int fNodeSize;

    static bool fgInitialized;
    static bool fgFinalized;
};

} // namespace MACE::Environment

#define MACE_MPI_MASTER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                      \
        MACE::Environment::MPIEnvironment::Instance().IsMaster())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_MASTER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or      \
        MACE::Environment::MPIEnvironment::Instance().IsMaster())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORKER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                      \
        MACE::Environment::MPIEnvironment::Instance().IsWorker())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORKER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or      \
        MACE::Environment::MPIEnvironment::Instance().IsWorker())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_MASTER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_MASTER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeMaster())                   \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_MASTER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeMaster())   \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_WORKER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_WORKER_OUT(verboseLevel, Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or                           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeWorker())                   \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_WORKER_OUT(Threshold, out) \
    if (not MACE::Environment::MPIEnvironment::Available() or           \
        MACE::Environment::MPIEnvironment::Instance().IsNodeWorker())   \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Environment/MPIEnvironment.inl"
