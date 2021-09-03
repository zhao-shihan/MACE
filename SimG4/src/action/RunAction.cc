#include "action/RunAction.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

RunAction::RunAction() :
    G4UserRunAction() {
    Analysis::Instance()->Initialize();
}

RunAction::~RunAction() {
    delete Analysis::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    Analysis::Instance()->Open();
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance()->WriteAndClose();
}
