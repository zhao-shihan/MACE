#include "G4MPImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"

#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::Action;

RunAction::RunAction() :
    G4UserRunAction() {
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* run) {
    firstTrueEventID = 0;
    if (MPI::Is_initialized()) {
        const auto* const mpiManager = G4MPImanager::GetManager();
        const int nEventOfThisRank = run->GetNumberOfEventToBeProcessed();
        std::vector<int> nEventOfAll(mpiManager->GetActiveSize());
        mpiManager->GetComm()->Allgather(std::addressof(nEventOfThisRank), 1, MPI::INT, nEventOfAll.data(), 1, MPI::INT);
        for (G4int i = 0; i < mpiManager->GetRank(); ++i) {
            firstTrueEventID += nEventOfAll[i];
        }
    }

    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().Close();
}
