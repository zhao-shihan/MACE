#pragma once

#include "MACE/Extension/Geant4X/Run/MPIRunManager.h++"

#include <memory>

namespace MACE::SimEMC {

class Analysis;

class RunManager final : public Geant4X::MPIRunManager {
public:
    RunManager();
    ~RunManager();

    static auto Instance() -> auto& { return static_cast<RunManager&>(*GetRunManager()); }

private:
    std::unique_ptr<Analysis> fAnalysis;
};

} // namespace MACE::SimEMC
