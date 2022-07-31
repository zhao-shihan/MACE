#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace MACE::Environment {

class MPIEnvironment : public BasicEnvironment {
public:
    MPIEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                   VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnvironment();

    static auto& Instance() { return static_cast<MPIEnvironment&>(BasicEnvironment::Instance()); }

    static const auto& WorldCommRank() { return Instance().fWorldCommRank; }
    static const auto& WorldCommSize() { return Instance().fWorldCommSize; }
    static const auto& ProcessorName() { return Instance().fProcessorName; }
    static auto IsWorldMaster() { return WorldCommRank() == 0; }
    static auto IsWorldWorker() { return WorldCommRank() > 0; }
    static auto IsSequential() { return WorldCommSize() == 1; }
    static auto IsParallel() { return WorldCommSize() > 1; }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPIAndWorldProperties(int argc, char* argv[]);

private:
    int fWorldCommRank;
    int fWorldCommSize;
    std::string fProcessorName;
};

} // namespace MACE::Environment

#define MACE_MPI_MASTER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::IsWorldMaster()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_MASTER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::IsWorldMaster())                        \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_MASTER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::IsWorldMaster())        \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)

#define MACE_MPI_WORKER_OUT(out)                                        \
    static_assert(std::derived_from<std::remove_cvref_t<decltype(out)>, \
                                    std::ostream>);                     \
    if (MACE::Environment::MPIEnvironment::IsWorldWorker()) out

#define MACE_VERBOSE_LEVEL_CONTROLLED_MPI_WORKER_OUT(verboseLevel, Threshold, out) \
    if (MACE::Environment::MPIEnvironment::IsWorldWorker())                        \
    MACE_VERBOSE_LEVEL_CONTROLLED_OUT(verboseLevel, Threshold, out)

#define MACE_ENVIRONMENT_CONTROLLED_MPI_WORKER_OUT(Threshold, out) \
    if (MACE::Environment::MPIEnvironment::IsWorldWorker())        \
    MACE_ENVIRONMENT_CONTROLLED_OUT(Threshold, out)
