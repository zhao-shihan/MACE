#include "MACE/SimEMC/Action/RunAction.h++"
// #include "MACE/SimEMC/Analysis.h++"

namespace MACE::SimEMC::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    // Analysis::Instance().RunBegin(run);
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    // Analysis::Instance().RunEnd();
}

} // namespace MACE::SimEMC::inline Action
