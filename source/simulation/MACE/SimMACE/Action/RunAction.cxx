#include "MACE/SimMACE/Action/RunAction.hxx"
#include "MACE/SimMACE/Analysis.hxx"

namespace MACE::SimMACE::Action {

void RunAction::BeginOfRunAction(const G4Run*) {
    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().Close();
}

} // namespace MACE::SimMACE::Action
