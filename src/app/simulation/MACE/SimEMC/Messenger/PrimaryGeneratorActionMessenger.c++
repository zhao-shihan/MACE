#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4UIcommand.hh"

namespace MACE::SimEMC::inline Messenger {

using namespace MACE::LiteralUnit::Frequency;

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton{},
    G4UImessenger{},
    fPrimaryGeneratorAction{},
    fSwitchToGPS{},
    fSwitchToCosmicRayMuon{} {

    fSwitchToGPS = std::make_unique<G4UIcommand>("/MACE/Generator/SwitchToGPS", this);
    fSwitchToGPS->SetGuidance("If set then the G4GeneralParticleSource will be used.");
    fSwitchToGPS->AvailableForStates(G4State_PreInit, G4State_Idle);

    fSwitchToCosmicRayMuon = std::make_unique<G4UIcommand>("/MACE/Generator/SwitchToCosmicRayMuon", this);
    fSwitchToCosmicRayMuon->SetGuidance("If set then the EcoMug generator will be used.");
    fSwitchToCosmicRayMuon->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String) {
    if (command == fSwitchToGPS.get()) {
        fPrimaryGeneratorAction->SwitchToGPS();
    } else if (command == fSwitchToCosmicRayMuon.get()) {
        fPrimaryGeneratorAction->SwitchToCosmicRayMuon();
    }
}

} // namespace MACE::SimEMC::inline Messenger
