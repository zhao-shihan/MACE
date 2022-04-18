#include "MACE/Simulation/SimTarget/Action/RunAction.hxx"
#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4Run.hh"

namespace MACE::Simulation::SimTarget::Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance().RunBegin(run);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::Simulation::SimTarget::Action
