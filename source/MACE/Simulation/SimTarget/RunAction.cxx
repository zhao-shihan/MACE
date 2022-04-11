#include "MACE/Simulation/SimTarget/Analysis.hxx"
#include "MACE/Simulation/SimTarget/RunAction.hxx"

namespace MACE::Simulation::SimTarget {

void RunAction::BeginOfRunAction(const G4Run*) {
    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().Close();
}

} // namespace MACE::Simulation::SimTarget
