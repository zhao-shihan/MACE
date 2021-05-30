#include "useraction/MACESteppingAction.hh"
#include "G4UnitsTable.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"
#include "useraction/MACEDetectorConstruction.hh"

MACESteppingAction::MACESteppingAction() :
    fPhysicalMagneticSpectrometerShield(static_cast<const MACEDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetPhysicalMagneticSpectrometerShield()),
    fPhysicalMagneticSpectrometerShieldCount(3),
    fPhysicalCsIShield(static_cast<const MACEDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetPhysicalCsIShield()),
    fPhysicalCsIShieldCount(2) {}

MACESteppingAction::~MACESteppingAction() {}

void MACESteppingAction::UserSteppingAction(const G4Step* step) {
    auto particle = step->GetTrack()->GetDefinition();
    if (particle == G4Electron::Definition() ||
        particle == G4Positron::Definition() ||
        particle == G4Gamma::Definition()) {
        auto nextVolume = step->GetTrack()->GetNextVolume();
        for (size_t i = 0; i < fPhysicalMagneticSpectrometerShieldCount; ++i) {
            if (nextVolume == fPhysicalMagneticSpectrometerShield[i]) {
                step->GetTrack()->SetTrackStatus(fStopAndKill);
                break;
            }
        }
        for (size_t i = 0; i < fPhysicalCsIShieldCount; ++i) {
            if (nextVolume == fPhysicalCsIShield[i]) {
                step->GetTrack()->SetTrackStatus(fStopAndKill);
                break;
            }
        }
    }

    if (step->GetTrack()->GetCurrentStepNumber() > 100000) {
        step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
}

