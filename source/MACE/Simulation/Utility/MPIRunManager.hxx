#pragma once

#include "MACE/Utility/DivideIndices.hxx"

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
    const auto& GetTotalNumberOfEventToBeProcessed() const { return fTotalNumberOfEventsToBeProcessed; }

    virtual void BeamOn(G4int nEvent, const char* macroFile = nullptr, G4int nSelect = -1) override;
    virtual void ProcessOneEvent(G4int eventID) override { G4RunManager::ProcessOneEvent(fEventIDRange.begin + fEventIDRange.step * eventID); }

private:
    G4bool CheckNEventIsAtLeastCommSize(G4int nEvent) const;

private:
    const int fCommRank;
    const int fCommSize;

    G4int fTotalNumberOfEventsToBeProcessed;
    MACE::Utility::DividedIndexRange<G4int> fEventIDRange;
};

} // namespace MACE::Simulation::Utility
