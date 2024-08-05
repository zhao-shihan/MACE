#include "MACE/SimMACE/Action/RunAction.h++"
#include "MACE/SimMACE/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimMACE::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBeginAction(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEndAction(run->GetRunID());
}

} // namespace MACE::SimMACE::inline Action
