#include "mpi.h"

#include "G4MPImanager.hh"
#include "G4StateManager.hh"

#include "MPITools/G4MPIRunManager.hxx"

using namespace MACE;

void G4MPIRunManager::SetG4MPImanager(const G4MPImanager& g4mpi) {
    auto currentState = G4StateManager::GetStateManager()->GetCurrentState();
    if (currentState == G4State_PreInit or currentState == G4State_Idle) {
        fG4mpi = std::addressof(g4mpi);
    } else {
        G4cerr << "Illegal application state - SetG4MPImanager() ignored." << G4endl;
    }
}

G4bool G4MPIRunManager::ConfirmBeamOnCondition() {
    if (MPI::Is_initialized() and fG4mpi == nullptr) {
        G4cerr << "G4MPImanager is not set while MPI is initialized - BeamOn() ignored.\n"
                  "Try invoke SetG4MPImanager(const G4MPImanager&) before BeamOn()."
               << G4endl;
        return false;
    }
    return G4RunManager::ConfirmBeamOnCondition();
}

void G4MPIRunManager::RunInitialization() {
    fFirstEventID = 0;
    if (fG4mpi != nullptr) {
        std::vector<decltype(numberOfEventToBeProcessed)> numberOfEventToBeProcessedRecv(fG4mpi->GetActiveSize());
        fG4mpi->GetComm()->Allgather(std::addressof(numberOfEventToBeProcessed), 1, MPI::INT, numberOfEventToBeProcessedRecv.data(), 1, MPI::INT);
        for (G4int i = 0; i < fG4mpi->GetRank(); ++i) {
            fFirstEventID += numberOfEventToBeProcessedRecv[i];
        }
    }
    G4RunManager::RunInitialization();
}
