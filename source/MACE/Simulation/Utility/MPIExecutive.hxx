#pragma once

namespace MACE::Simulation::Utility {

class MPIExecutive {
public:
    MPIExecutive(int argc, char** argv);
    virtual ~MPIExecutive() = default;
    MPIExecutive(const MPIExecutive&) = delete;
    MPIExecutive& operator=(const MPIExecutive&) = delete;

    virtual void StartInteractiveSession(const char* initializeMacro = nullptr);
    virtual void StartBatchSession(const char* macro);

protected:
    int fArgc;
    char** fArgv;
};

} // namespace MACE::Simulation::Utility
