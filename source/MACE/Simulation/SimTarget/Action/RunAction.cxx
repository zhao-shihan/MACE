#include "MACE/Simulation/SimTarget/Action/RunAction.hxx"
#include "MACE/Simulation/SimTarget/Analysis.hxx"

#include "G4Run.hh"

namespace MACE::Simulation::SimTarget::Action {

void RunAction::EndOfRunAction(const G4Run* run) {
    Analysis::Instance().Write(run->GetRunID());
}

} // namespace MACE::Simulation::SimTarget::Action
