#include "Simulation/SimMACE/Action/RunAction.hxx"
#include "Simulation/SimMACE/Utility/Analysis.hxx"

namespace MACE::Simulation::SimMACE::Action {

using Utility::Analysis;

void RunAction::BeginOfRunAction(const G4Run*) {
    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().Close();
}

} // namespace MACE::Simulation::SimMACE::Action
