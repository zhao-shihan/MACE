#pragma once

namespace MACE::SimulationG4 {

class MPIExecutive {
public:
    MPIExecutive();
    virtual ~MPIExecutive() = default;
    MPIExecutive(const MPIExecutive&) = delete;
    MPIExecutive& operator=(const MPIExecutive&) = delete;

    virtual void StartInteractiveSession(int argc, char* argv[], const char* initializeMacro = nullptr);
    virtual void StartBatchSession(const char* macro);
};

} // namespace MACE::SimulationG4
