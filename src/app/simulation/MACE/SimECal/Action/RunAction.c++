#include "MACE/SimECal/Action/RunAction.h++"
#include "MACE/SimECal/Analysis.h++"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"

namespace MACE::SimECal::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBegin(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimECal::inline Action
