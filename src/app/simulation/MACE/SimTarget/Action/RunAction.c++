#include "MACE/SimTarget/Action/RunAction.h++"
#include "MACE/SimTarget/Analysis.h++"

namespace MACE::SimTarget::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBegin(run);
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimTarget::inline Action
