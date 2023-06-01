#include "MACE/SimTarget/Action/RunAction.h++"
#include "MACE/SimTarget/Analysis.h++"

namespace MACE::SimTarget::inline Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance().RunBegin(run);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimTarget::inline Action
