#include "MACE/SimPTS/Action/RunAction.h++"
#include "MACE/SimPTS/Analysis.h++"

#include "G4Run.hh"

namespace MACE::SimPTS::inline Action {

RunAction::RunAction() :
    PassiveSingleton{this},
    G4UserRunAction{} {}

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBegin(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run*) -> void {
    Analysis::Instance().RunEnd();
}

} // namespace MACE::SimPTS::inline Action
