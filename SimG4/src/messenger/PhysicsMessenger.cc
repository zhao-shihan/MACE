#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

#include "messenger/PhysicsMessenger.hh"
#include "physics/MuoniumProduction.hh"

using namespace MACE::SimG4;

PhysicsMessenger* PhysicsMessenger::Instance() {
    static PhysicsMessenger instance;
    return &instance;
}

PhysicsMessenger::PhysicsMessenger() :
    G4UImessenger(),
    fpMuoniumProduction(nullptr) {

    fDirectory = new G4UIdirectory("/MACE/Physics/");
    fDirectory->SetGuidance("MACE Physics.");

    fSetConversionProbability = new G4UIcmdWithADouble("/MACE/Physics/SetConversionProbability", this);
    fSetConversionProbability->SetGuidance("Set probability of muonium to anti-muonium conversion.");
    fSetConversionProbability->SetParameterName("P", false);
    fSetConversionProbability->AvailableForStates(G4State_Idle);
}

PhysicsMessenger::~PhysicsMessenger() {
    delete fSetConversionProbability;
    delete fDirectory;
}

void PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetConversionProbability) {
        fpMuoniumProduction->SetConversionProbability(fSetConversionProbability->GetNewDoubleValue(value));
    }
}
