#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"

#include <string>

namespace MACE::Environment {

class MPIEnvironment : public BasicEnvironment {
public:
    MPIEnvironment(int& argc, char**& argv, VerboseLevel verboseLevel = VerboseLevel::Warning, bool printStartupMessage = true);
    virtual ~MPIEnvironment();

    static auto Initialized() { return fgMPIEnvironmentInstance != nullptr; }
    static auto Finalized() { return fgMPIEnvironmentFinalized; }
    static auto Available() { return Initialized() and not Finalized(); }
    static auto& Instance() { return *fgMPIEnvironmentInstance; }

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
    int fWorldCommRank;
    int fWorldCommSize;
    std::string fProcessorName;

    static ObserverPtr<MPIEnvironment> fgMPIEnvironmentInstance;
    static bool fgMPIEnvironmentFinalized;
};

} // namespace MACE::Environment
