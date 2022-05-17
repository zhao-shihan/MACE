#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.hxx"

#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

namespace MACE::Simulation::Physics::Messenger {

MuoniumPhysicsMessenger& MuoniumPhysicsMessenger::Instance() {
    static MuoniumPhysicsMessenger instance;
    return instance;
}

MuoniumPhysicsMessenger::MuoniumPhysicsMessenger() :
    G4UImessenger(),
    fMuoniumPhysicsDirectory("/MACE/Physics/MuoniumPhysics/"),
    fFormationProcessDirectory("/MACE/Physics/MuoniumPhysics/Formation/"),
    fSetFormationProbability("/MACE/Physics/MuoniumPhysics/Formation/SetFormationProbability", this),
    fSetConversionProbability("/MACE/Physics/MuoniumPhysics/Formation/SetConversionProbability", this),
    fTransportProcessDirectory("/MACE/Physics/MuoniumPhysics/Transport/"),
    fSetMeanFreePath("/MACE/Physics/MuoniumPhysics/Transport/SetMeanFreePath", this),
    fSetManipulateAllStepInFlight("/MACE/Physics/MuoniumPhysics/Transport/SetManipulateAllStepInFlight", this) {

    fMuoniumPhysicsDirectory.SetGuidance("Physics of muonium and anti-muonium.");

    fFormationProcessDirectory.SetGuidance("Muonium formation and transition process.");

    fSetFormationProbability.SetGuidance("Set integrated probability of rest mu+ captures a e- in the target.");
    fSetFormationProbability.SetParameterName("P", false);
    fSetFormationProbability.AvailableForStates(G4State_Idle);

    fSetConversionProbability.SetGuidance("Set integrated probability of muonium to anti-muonium conversion.");
    fSetConversionProbability.SetParameterName("P", false);
    fSetConversionProbability.AvailableForStates(G4State_Idle);

    fTransportProcessDirectory.SetGuidance("The transport process of thermal muonium in the target.");

    fSetMeanFreePath.SetGuidance("Set thermal muonium mean free path in the target.");
    fSetMeanFreePath.SetParameterName("lambda", false);
    fSetMeanFreePath.SetUnitCategory("Length");
    fSetMeanFreePath.AvailableForStates(G4State_Idle);

    fSetManipulateAllStepInFlight.SetGuidance(
        "Set whether show each step of thermal random flight of muonium in the target or not.\n"
        "Warning: This can be time consuming if set to true.");
    fSetManipulateAllStepInFlight.SetParameterName("b", false);
    fSetManipulateAllStepInFlight.AvailableForStates(G4State_Idle);
}

void MuoniumPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetFormationProbability)) {
        fMuoniumFormation->SetFormationProbability(fSetFormationProbability.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetConversionProbability)) {
        fMuoniumFormation->SetConversionProbability(fSetConversionProbability.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetMeanFreePath)) {
        fMuoniumTransport->SetMeanFreePath(fSetMeanFreePath.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetManipulateAllStepInFlight)) {
        fMuoniumTransport->SetManipulateAllStepInFlight(fSetManipulateAllStepInFlight.GetNewBoolValue(value));
    }
}

} // namespace MACE::Simulation::Physics::Messenger
