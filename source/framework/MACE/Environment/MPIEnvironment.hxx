#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/Memory/FreeSingleton.hxx"

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace MACE::Environment {

class MPIEnvironment : public BasicEnvironment,
                       public Memory::FreeSingleton<MPIEnvironment> {
public:
    MPIEnvironment(int argc, char* argv[], std::optional<std::reference_wrapper<CLI::BasicCLI>> optCLI,
                   VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnvironment();

    static auto& Instance() { return FreeSingleton<MPIEnvironment>::Instance(); }

    static const auto& WorldCommRank() { return Instance().fWorldCommRank; }
    static const auto& WorldCommSize() { return Instance().fWorldCommSize; }
    static const auto& ProcessorName() { return Instance().fProcessorName; }
    static auto IsWorldMaster() { return WorldCommRank() == 0; }
    static auto IsWorldWorker() { return WorldCommRank() > 0; }
    static auto IsSerialized() { return WorldCommSize() == 1; }
    static auto IsParallelized() { return WorldCommSize() > 1; }

protected:
    void PrintStartupMessageBody(int argc, char* argv[]) const;

private:
    void InitializeMPIAndWorldProperties(int argc, char** argv);

private:
    int fWorldCommRank;
    int fWorldCommSize;
    std::string fProcessorName;
};

} // namespace MACE::Environment
