#pragma once

#include "G4RunManager.hh"

namespace MACE::Simulation::Utility {

class MPIRunManager : public G4RunManager {
public:
    MPIRunManager();
    virtual ~MPIRunManager() noexcept = default;
    MPIRunManager(const MPIRunManager&) = delete;
    MPIRunManager& operator=(const MPIRunManager&) = delete;

    virtual void BeamOn(G4int nEvent, const char* macroFile = nullptr, G4int nSelect = -1) override;
    virtual void ProcessOneEvent(G4int eventID) override { G4RunManager::ProcessOneEvent(fCommSize * eventID + fCommRank); }

private:
    void DistributeSeed() const;
    int DistributeEvent(G4int nEvent) const;

    static void CheckMPI();

private:
    int fCommRank;
    int fCommSize;
};

} // namespace MACE::Simulation::Utility
