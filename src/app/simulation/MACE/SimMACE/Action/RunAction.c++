#include "MACE/SimMACE/Action/RunAction.h++"
#include "MACE/SimMACE/Data/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimMACE::inline Action {

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Data::Analysis::Instance().RunBegin(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Data::Analysis::Instance().RunEnd();
}

} // namespace MACE::SimMACE::inline Action
