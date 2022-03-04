#pragma once

#include "G4RunManager.hh"

#include "UtilityForwardDeclaration.hxx"
#include "ObserverPtr.hxx"

class G4MPImanager;

class MACE::G4MPIRunManager :
    public G4RunManager {
public:
    G4MPIRunManager() = default;
    virtual ~G4MPIRunManager() noexcept = default;
    G4MPIRunManager(const G4MPIRunManager&) = delete;
    G4MPIRunManager& operator=(const G4MPIRunManager&) = delete;

    void SetG4MPImanager(const G4MPImanager& g4mpi);

    G4bool ConfirmBeamOnCondition() override;
    void RunInitialization() override;
    void ProcessOneEvent(G4int eventID) override { G4RunManager::ProcessOneEvent(fFirstEventID + eventID); }

private:
    ObserverPtr<const G4MPImanager> fG4mpi = nullptr;
    G4int fFirstEventID = 0;
};
