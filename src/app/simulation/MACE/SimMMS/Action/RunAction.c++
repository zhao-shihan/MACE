#include "MACE/SimMMS/Action/RunAction.h++"
#include "MACE/SimMMS/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimMMS::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBeginAction(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEndAction(run->GetRunID());
}

} // namespace MACE::SimMMS::inline Action
