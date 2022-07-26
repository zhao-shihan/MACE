#pragma once

#include "MACE/Environment/Memory/FreeSingleton.hxx"

namespace MACE::SimulationG4 {

class MPIExecutive : public Environment::Memory::FreeSingleton<MPIExecutive> {
public:
    virtual ~MPIExecutive() = default;

    virtual void StartInteractiveSession(int argc, char* argv[], const char* initializeMacro = nullptr);
    virtual void StartBatchSession(const char* macro);
};

} // namespace MACE::SimulationG4
