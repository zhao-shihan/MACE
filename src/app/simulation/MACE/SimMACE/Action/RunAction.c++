#include "MACE/SimMACE/Action/RunAction.h++"
#include "MACE/SimMACE/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimMACE::inline Action {

auto RunAction::BeginOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunBegin();
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEnd(run->GetRunID());
}

} // namespace MACE::SimMACE::inline Action
