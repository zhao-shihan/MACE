#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcommand.hh"

namespace MACE::SimEMC::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fSwitchToGPS{},
    fSwitchToEcoMug{} {

    fSwitchToGPS = std::make_unique<G4UIcommand>("/MACE/Generator/SwitchToGPS", this);
    fSwitchToGPS->SetGuidance("If set then the G4GeneralParticleSource will be used.");
    fSwitchToGPS->AvailableForStates(G4State_PreInit, G4State_Idle);

    fSwitchToEcoMug = std::make_unique<G4UIcommand>("/MACE/Generator/SwitchToEcoMug", this);
    fSwitchToEcoMug->SetGuidance("If set then the EcoMug generator will be used.");
    fSwitchToEcoMug->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String) {
    if (command == fSwitchToGPS.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToGPS();
        });
    } else if (command == fSwitchToEcoMug.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToEcoMug();
        });
    }
}

} // namespace MACE::SimEMC::inline Messenger
