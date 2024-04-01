#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMMS::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fSavePrimaryVertexData{},
    fSaveDecayVertexData{},
    fCoincidenceWithCDC{},
    fCoincidenceWithTTC{},
    fSaveCDCHitData{},
    fSaveTTCHitData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMMS::Analysis controller.");

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this);
    fFilePath->SetGuidance("Set file path.");
    fFilePath->SetParameterName("path", false);
    fFilePath->AvailableForStates(G4State_Idle);

    fFileMode = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileMode", this);
    fFileMode->SetGuidance("Set mode (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileMode->SetParameterName("mode", false);
    fFileMode->AvailableForStates(G4State_Idle);

    fSavePrimaryVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SavePrimaryVertexData", this);
    fSavePrimaryVertexData->SetGuidance("Save primary vertex data if enabled.");
    fSavePrimaryVertexData->SetParameterName("mode", false);
    fSavePrimaryVertexData->AvailableForStates(G4State_Idle);

    fSaveDecayVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveDecayVertexData", this);
    fSaveDecayVertexData->SetGuidance("Save decay vertex data if enabled.");
    fSaveDecayVertexData->SetParameterName("mode", false);
    fSaveDecayVertexData->AvailableForStates(G4State_Idle);

    fCoincidenceWithCDC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithCDC", this);
    fCoincidenceWithCDC->SetGuidance("Coincidence with CDC if enabled.");
    fCoincidenceWithCDC->SetParameterName("mode", false);
    fCoincidenceWithCDC->AvailableForStates(G4State_Idle);

    fCoincidenceWithTTC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithTTC", this);
    fCoincidenceWithTTC->SetGuidance("Coincidence with TTC if enabled.");
    fCoincidenceWithTTC->SetParameterName("mode", false);
    fCoincidenceWithTTC->AvailableForStates(G4State_Idle);

    fSaveCDCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveCDCHitData", this);
    fSaveCDCHitData->SetGuidance("Save CDC hit data if enabled.");
    fSaveCDCHitData->SetParameterName("mode", false);
    fSaveCDCHitData->AvailableForStates(G4State_Idle);

    fSaveTTCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveTTCHitData", this);
    fSaveTTCHitData->SetGuidance("Save TTC hit data if enabled.");
    fSaveTTCHitData->SetParameterName("mode", false);
    fSaveTTCHitData->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fFilePath.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FilePath(std::string_view(value));
        });
    } else if (command == fFileMode.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FileMode(value);
        });
    } else if (command == fSavePrimaryVertexData.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SavePrimaryVertexData(fSavePrimaryVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithCDC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithCDC(fCoincidenceWithCDC->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithTTC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithTTC(fCoincidenceWithTTC->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveCDCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveCDCHitData(fSaveCDCHitData->GetNewBoolValue(value));
        });
    } else if (command == fSaveTTCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveTTCHitData(fSaveTTCHitData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMMS::inline Messenger
