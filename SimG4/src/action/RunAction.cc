#include "G4MPImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "action/RunAction.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "action/EventAction.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

RunAction::RunAction(PrimaryGeneratorAction* pPrimaryGeneratorAction, EventAction* pEventAction) :
    G4UserRunAction(),
    fpPrimaryGeneratorAction(pPrimaryGeneratorAction),
    fpEventAction(pEventAction) {
    Analysis::Instance()->Initialize();
}

RunAction::~RunAction() {
    delete Analysis::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance()->Open();

    G4int firstPluseIDOfThisRank = 0;
    if (MPI::Is_initialized()) {
        const auto* const mpiManager = G4MPImanager::GetManager();
        const int thisNumberOfEvent = run->GetNumberOfEventToBeProcessed();
        int* allNumberOfEvent = new int[mpiManager->GetActiveSize()];
        mpiManager->GetComm()->Allgather(&thisNumberOfEvent, 1, MPI::INT, allNumberOfEvent, 1, MPI::INT);
        for (G4int i = 0; i < mpiManager->GetRank(); ++i) {
            firstPluseIDOfThisRank += allNumberOfEvent[i];
        }
        delete[] allNumberOfEvent;
    }
    fpPrimaryGeneratorAction->SetFirstPluseIDOfThisRank(firstPluseIDOfThisRank);
    fpEventAction->SetFirstPluseIDOfThisRank(firstPluseIDOfThisRank);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance()->WriteAndClose();
}
