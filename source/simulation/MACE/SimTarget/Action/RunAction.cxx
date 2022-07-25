#include "MACE/SimTarget/Action/RunAction.hxx"
#include "MACE/SimTarget/RunManager.hxx"

#include "G4Run.hh"

namespace MACE::SimTarget::Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    RunManager::Instance().GetAnalysis().RunBegin(run);
}

void RunAction::EndOfRunAction(const G4Run*) {
    RunManager::Instance().GetAnalysis().RunEnd();
}

} // namespace MACE::SimTarget::Action
