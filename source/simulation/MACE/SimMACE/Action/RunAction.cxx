#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimMACE/RunManager.hxx"

#include "G4Run.hh"

namespace MACE::SimMACE::Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    RunManager::Instance().GetAnalysis().RunBegin(run->GetRunID());
}

void RunAction::EndOfRunAction(const G4Run*) {
    RunManager::Instance().GetAnalysis().RunEnd();
}

} // namespace MACE::SimMACE::Action
