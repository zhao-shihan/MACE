#pragma once

#include "MACE/Extension/Geant4X/MPIRunManager.h++"

#include <memory>

namespace MACE::SimMMS {

class Analysis;

class RunManager final : public Geant4X::MPIRunManager {
public:
    RunManager();
    ~RunManager();

    static auto Instance() -> auto& { return static_cast<RunManager&>(*GetRunManager()); }

private:
    std::unique_ptr<Analysis> fAnalysis;
};

} // namespace MACE::SimMMS
