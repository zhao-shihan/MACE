#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimMACE/RunManager.hxx"

namespace MACE::SimMACE::Action {

void RunAction::BeginOfRunAction(const G4Run*) {
    RunManager::Instance().GetAnalysis().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    RunManager::Instance().GetAnalysis().Close();
}

} // namespace MACE::SimMACE::Action
