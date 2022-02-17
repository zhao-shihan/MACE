#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

#include "SimMACE/Messenger/PhysicsMessenger.hxx"
#include "SimMACE/Physics/MuoniumProduction.hxx"

using namespace MACE::SimMACE::Messenger;

PhysicsMessenger& PhysicsMessenger::Instance() {
    static PhysicsMessenger instance;
    return instance;
}

PhysicsMessenger::PhysicsMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Physics/"),
    fSetConversionProbability("/MACE/Physics/SetConversionProbability", this) {

    fDirectory.SetGuidance("MACE Physics.");

    fSetConversionProbability.SetGuidance("Set probability of muonium to anti-muonium conversion.");
    fSetConversionProbability.SetParameterName("P", false);
    fSetConversionProbability.AvailableForStates(G4State_Idle);
}

void PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetConversionProbability)) {
        fMuoniumProduction->SetConversionProbability(fSetConversionProbability.GetNewDoubleValue(value));
    }
}
