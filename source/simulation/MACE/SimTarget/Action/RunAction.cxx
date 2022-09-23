#include "MACE/SimTarget/Action/RunAction.hxx"
#include "MACE/SimTarget/Analysis.hxx"

namespace MACE::SimTarget::Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance().RunBegin(run);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimTarget::Action
