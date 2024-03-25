#include "MACE/SimMMS/Action/RunAction.h++"
#include "MACE/SimMMS/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimMMS::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBegin(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimMMS::inline Action
