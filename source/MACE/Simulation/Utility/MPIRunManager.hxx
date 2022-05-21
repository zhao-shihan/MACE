#pragma once

#include "G4RunManager.hh"

namespace MACE::Simulation::Utility {

class MPIRunManager : public G4RunManager {
public:
    MPIRunManager();
    virtual ~MPIRunManager() noexcept = default;
    MPIRunManager(const MPIRunManager&) = delete;
    MPIRunManager& operator=(const MPIRunManager&) = delete;

    static auto GetRunManager() { return static_cast<MPIRunManager*>(G4RunManager::GetRunManager()); }

    const auto& GetCommRank() const { return fCommRank; }
    const auto& GetCommSize() const { return fCommSize; }

    virtual void BeamOn(G4int nEvent, const char* macroFile = nullptr, G4int nSelect = -1) override;
    virtual void ProcessOneEvent(G4int eventID) override { G4RunManager::ProcessOneEvent(fCommSize * eventID + fCommRank); }

private:
    void CheckNEventIsAtLeastCommSize(G4int nEvent) const;
    void DistributeSeed() const;
    int DistributeEvent(G4int nEvent) const;

    static void CheckMPI();
    static int ConstructorGetMPICommRank();
    static int ConstructorGetMPICommSize();

private:
    const int fCommRank;
    const int fCommSize;
};

} // namespace MACE::Simulation::Utility
