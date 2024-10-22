#include "MACE/Simulation/Physics/StandardPhysicsList.h++"
#include "MACE/Simulation/Physics/StandardPhysicsListMessenger.h++"

#include "G4UIcmdWithoutParameter.hh"
#include "G4UnitsTable.hh"

namespace MACE::inline Simulation::inline Physics {

StandardPhysicsListMessenger::StandardPhysicsListMessenger() :
    SingletonMessenger{},
    fUseRadioactiveDecayPhysics{},
    fUseOpticalPhysics{},
    fDisableMuonMinusCapture{} {

    fUseRadioactiveDecayPhysics = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Physics/UseRadioactiveDecayPhysics", this);
    fUseRadioactiveDecayPhysics->SetGuidance("If set, the G4RadioactiveDecayPhysics will be registered in the physics list.");
    fUseRadioactiveDecayPhysics->AvailableForStates(G4State_PreInit);

    fUseOpticalPhysics = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Physics/UseOpticalPhysics", this);
    fUseOpticalPhysics->SetGuidance("If set, the G4OpticalPhysics will be registered in the physics list.");
    fUseOpticalPhysics->AvailableForStates(G4State_PreInit);

    fDisableMuonMinusCapture = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Physics/DisableMuonMinusCapture", this);
    fDisableMuonMinusCapture->SetGuidance("If set, nuclear stopping of mu- will not be constructed in G4StoppingPhysics.");
    fDisableMuonMinusCapture->AvailableForStates(G4State_PreInit);
}

StandardPhysicsListMessenger::~StandardPhysicsListMessenger() = default;

auto StandardPhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String) -> void {
    if (command == fUseRadioactiveDecayPhysics.get()) {
        Deliver<StandardPhysicsListBase>([&](auto&& r) {
            r.UseRadioactiveDecayPhysics();
        });
    } else if (command == fUseOpticalPhysics.get()) {
        Deliver<StandardPhysicsListBase>([&](auto&& r) {
            r.UseOpticalPhysics();
        });
    } else if (command == fDisableMuonMinusCapture.get()) {
        Deliver<StandardPhysicsListBase>([&](auto&& r) {
            r.DisableMuonMinusCapture();
        });
    }
}

} // namespace MACE::inline Simulation::inline Physics
