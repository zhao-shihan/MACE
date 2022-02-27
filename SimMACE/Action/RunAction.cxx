#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::Action;

void RunAction::BeginOfRunAction(const G4Run*) {
    Analysis::Instance().Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance().Close();
}
