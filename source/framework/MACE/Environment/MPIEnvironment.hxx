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
    template<class ACLI = Detail::NoCLI>
    MPIEnvironment(int argc, char* argv[], ACLI&& cli, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnvironment();

    using FreeSingleton<MPIEnvironment>::Instance;

    const auto& WorldCommRank() const { return fWorldCommRank; }
    const auto& WorldCommSize() const { return fWorldCommSize; }
    auto IsMaster() const { return WorldCommRank() == 0; }
    auto IsWorker() const { return WorldCommRank() > 0; }
    auto IsSequential() const { return WorldCommSize() == 1; }
    auto IsParallel() const { return WorldCommSize() > 1; }

    const auto& NodeInfoList() const { return fNodeInfoList; }
    const auto& NodeInfo() const { return *fLocalNodeInfo; }
    const auto& NodeSize() const { return fLocalNodeInfo->first; }
    const auto& NodeName() const { return fLocalNodeInfo->second; }
    const auto& NodeInfo(std::size_t id) { return NodeInfoList()[id]; }
    const auto& NodeSize(std::size_t id) { return NodeInfo(id).first; }
    const auto& NodeName(std::size_t id) { return NodeInfo(id).second; }
    const auto& NodeId() const { return fNodeId; }
    auto NumberOfNodes() const { return NodeInfoList().size(); }
    auto OnSingleNode() const { return NumberOfNodes() == 1; }
    auto OnCluster() const { return NumberOfNodes() > 1; }

    const auto& NodeComm() const { return fNodeComm; }
    const auto& NodeCommRank() const { return fNodeCommRank; }
    const auto& NodeCommSize() const { return fNodeCommSize; }
    auto IsNodeMaster() const { return NodeCommRank() == 0; }
    auto IsNodeWorker() const { return NodeCommRank() > 0; }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPI(int argc, char* argv[]);
    void InitializeNodeInfos();

private:
    int fWorldCommRank;
    int fWorldCommSize;

    std::vector<std::pair<int, std::string>> fNodeInfoList;
    decltype(fNodeInfoList)::const_iterator fLocalNodeInfo;
    int fNodeId;

    MPI_Comm fNodeComm;
    int fNodeCommRank;
    int fNodeCommSize;
};

} // namespace MACE::Environment

#define MACE_MPI_MASTER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::Instance().IsMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_MASTER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsMaster())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_MASTER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsMaster())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORKER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::Instance().IsWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORKER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsWorker())                  \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORKER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsWorker())  \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_MASTER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_MASTER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeMaster())                   \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_MASTER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeMaster())   \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_NODE_WORKER_OUT(out)                                   \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_NODE_WORKER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeWorker())                   \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_NODE_WORKER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::Instance().IsNodeWorker())   \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#include "MACE/Environment/MPIEnvironment.inl"
