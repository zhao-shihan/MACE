#include "G4MPImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "SimG4/Action/RunAction.hh"
#include "SimG4/Action/PrimaryGeneratorAction.hh"
#include "SimG4/Action/EventAction.hh"
#include "SimG4/Analysis.hh"

using namespace MACE::SimG4::Action;

RunAction::RunAction(PrimaryGeneratorAction* pPrimaryGeneratorAction, EventAction* pEventAction) :
    G4UserRunAction(),
    fpPrimaryGeneratorAction(pPrimaryGeneratorAction),
    fpEventAction(pEventAction),
    fpAnalysis(Analysis::Instance()) {}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run* run) {
    G4int firstTrueEventIDOfThisRank = 0;
    if (MPI::Is_initialized()) {
        const auto* const mpiManager = G4MPImanager::GetManager();
        const int thisNumberOfEvent = run->GetNumberOfEventToBeProcessed();
        int* allNumberOfEvent = new int[mpiManager->GetActiveSize()];
        mpiManager->GetComm()->Allgather(&thisNumberOfEvent, 1, MPI::INT, allNumberOfEvent, 1, MPI::INT);
        for (G4int i = 0; i < mpiManager->GetRank(); ++i) {
            firstTrueEventIDOfThisRank += allNumberOfEvent[i];
        }
        delete[] allNumberOfEvent;
    }
    fpPrimaryGeneratorAction->SetFirstTrueEventIDOfThisRank(firstTrueEventIDOfThisRank);
    fpEventAction->SetFirstTrueEventIDOfThisRank(firstTrueEventIDOfThisRank);

    fpAnalysis->Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    fpAnalysis->Close();
}
