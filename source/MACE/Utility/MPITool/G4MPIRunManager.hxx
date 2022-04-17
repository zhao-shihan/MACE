#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4MPImanager.hh"
#include "G4RunManager.hh"

namespace MACE::Utility::MPITool {

class G4MPIRunManager : public G4RunManager {
public:
    G4MPIRunManager() = default;
    virtual ~G4MPIRunManager() noexcept = default;
    G4MPIRunManager(const G4MPIRunManager&) = delete;
    G4MPIRunManager& operator=(const G4MPIRunManager&) = delete;

    ObserverPtr<G4MPImanager> InitializeG4MPI(int argc, char** argv);

    G4bool ConfirmBeamOnCondition() override;
    void RunInitialization() override;
    void ProcessOneEvent(G4int eventID) override { G4RunManager::ProcessOneEvent(fFirstEventID + eventID); }

private:
    std::unique_ptr<G4MPImanager> fG4mpi = nullptr;
    G4int fFirstEventID = 0;
};

} // namespace MACE::Utility::MPITool
