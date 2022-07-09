#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include <string>

namespace MACE::Utility::MPIUtil {

class MPIEnvironment final {
public:
    MPIEnvironment(int argc, char* argv[]);
    ~MPIEnvironment();
    MPIEnvironment(const MPIEnvironment&) = delete;
    MPIEnvironment& operator=(const MPIEnvironment&) = delete;

    static auto Available() { return fgInstance != nullptr; }
    static const auto& WorldCommRank() { return fgInstance->fWorldCommRank; }
    static const auto& WorldCommSize() { return fgInstance->fWorldCommSize; }
    static const auto& ProcessorName() { return fgInstance->fProcessorName; }
    static auto IsWorldMaster() { return WorldCommRank() == 0; }
    static auto IsWorldWorker() { return WorldCommRank() > 0; }
    static auto IsSerialized() { return WorldCommSize() == 1; }
    static auto IsParallelized() { return WorldCommSize() > 1; }

private:
    int fWorldCommRank;
    int fWorldCommSize;
    std::string fProcessorName;

    static ObserverPtr<MPIEnvironment> fgInstance;
};

} // namespace MACE::Utility::MPIUtil
