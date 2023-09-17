#include "MACE/Simulation/SimTarget/Action/RunAction.h++"
#include "MACE/Simulation/SimTarget/Analysis.h++"

namespace MACE::inline Simulation::SimTarget::inline Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance().RunBegin(run);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::inline Simulation::SimTarget::inline Action
