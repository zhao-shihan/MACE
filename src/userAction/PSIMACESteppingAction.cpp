#include "userAction/PSIMACESteppingAction.hh"
#include "G4UnitsTable.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "userAction/PSIMACEDetectorConstruction.hh"

PSIMACESteppingAction::PSIMACESteppingAction() :
    fPhysicalMagneticSpectrometerShield(static_cast<const PSIMACEDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetPhysicalMagneticSpectrometerShield()),
    fPhysicalMagneticSpectrometerShieldCount(3),
    fPhysicalCsIShield(static_cast<const PSIMACEDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetPhysicalCsIShield()),
    fPhysicalCsIShieldCount(2) {}

PSIMACESteppingAction::~PSIMACESteppingAction() {}

void PSIMACESteppingAction::UserSteppingAction(const G4Step* step) {
    if (step->GetTrack()->GetDefinition() == G4Electron::Definition() ||
        step->GetTrack()->GetDefinition() == G4Positron::Definition()) {
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

