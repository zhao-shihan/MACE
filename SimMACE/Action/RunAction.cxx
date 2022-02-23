#include "G4MPImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Action;

RunAction::RunAction(ObserverPtr<PrimaryGeneratorAction> primaryGeneratorAction, ObserverPtr<EventAction> eventAction) :
    G4UserRunAction(),
    fPrimaryGeneratorAction(primaryGeneratorAction),
    fEventAction(eventAction) {
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}

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
    fPrimaryGeneratorAction->SetFirstTrueEventIDOfThisRank(firstTrueEventIDOfThisRank);
    fEventAction->SetFirstTrueEventIDOfThisRank(firstTrueEventIDOfThisRank);

    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto&& analysis = Analysis::Instance();
    analysis.Close();
    analysis.Merge();
}
