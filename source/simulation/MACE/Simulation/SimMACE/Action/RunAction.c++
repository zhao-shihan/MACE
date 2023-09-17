#include "MACE/Simulation/SimMACE/Action/RunAction.h++"
#include "MACE/Simulation/SimMACE/Analysis.h++"

#include "G4Run.hh"

namespace MACE::inline Simulation::SimMACE::inline Action {

void RunAction::BeginOfRunAction(const G4Run* run) {
    Analysis::Instance().RunBegin(run->GetRunID());
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::inline Simulation::SimMACE::inline Action
