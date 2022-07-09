#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

namespace MACE::Utility::MPIUtil {

class MPIEnvironment {
public:
    MPIEnvironment(int argc, char* argv[]);
    ~MPIEnvironment();
    MPIEnvironment(const MPIEnvironment&) = delete;
    MPIEnvironment& operator=(const MPIEnvironment&) = delete;

    static auto GetWorldCommRank() { return fgInstance->fWorldCommRank; }
    static auto GetWorldCommSize() { return fgInstance->fWorldCommRank; }

private:
    int fWorldCommRank;
    int fWorldCommSize;

    static ObserverPtr<MPIEnvironment> fgInstance;
};

} // namespace MACE::Utility::MPIUtil
