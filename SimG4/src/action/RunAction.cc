#include <sstream>

#include "G4MPImanager.hh"

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
    G4String fileName = "MACE_SimG4";
    if (MPI::Is_initialized()) {
        std::stringstream ss;
        ss << fileName << "_rank" << G4MPImanager::GetManager()->GetRank();
        ss >> fileName;
    }
    Analysis::Instance()->Open(fileName);
}

void RunAction::EndOfRunAction(const G4Run*) {
    Analysis::Instance()->WriteAndClose();
}
