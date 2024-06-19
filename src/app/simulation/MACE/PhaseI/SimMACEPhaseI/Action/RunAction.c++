#include "MACE/PhaseI/SimMACEPhaseI/Action/RunAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBegin(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
