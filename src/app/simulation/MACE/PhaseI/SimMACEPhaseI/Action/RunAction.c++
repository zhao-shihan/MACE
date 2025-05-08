#include "MACE/PhaseI/SimMACEPhaseI/Action/RunAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

RunAction::RunAction() :
    PassiveSingleton{this},
    G4UserRunAction{} {}

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBeginAction(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEndAction(run->GetRunID());
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
