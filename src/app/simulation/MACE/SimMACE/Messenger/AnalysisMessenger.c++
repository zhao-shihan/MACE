#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Action/TrackingAction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMACE::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSavePrimaryVertexData{},
    fSaveDecayVertexData{},
    fCoincidenceWithMMS{},
    fCoincidenceWithMCP{},
    fCoincidenceWithECal{},
    fSaveTTCHitData{},
    fSaveCDCHitData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMACE::Analysis controller.");

    fSavePrimaryVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SavePrimaryVertexData", this);
    fSavePrimaryVertexData->SetGuidance("Save primary vertex data if enabled.");
    fSavePrimaryVertexData->SetParameterName("mode", false);
    fSavePrimaryVertexData->AvailableForStates(G4State_Idle);

    fSaveDecayVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveDecayVertexData", this);
    fSaveDecayVertexData->SetGuidance("Save decay vertex data if enabled.");
    fSaveDecayVertexData->SetParameterName("mode", false);
    fSaveDecayVertexData->AvailableForStates(G4State_Idle);

    fCoincidenceWithMMS = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMMS", this);
    fCoincidenceWithMMS->SetGuidance("Coincidence with MMS if enabled.");
    fCoincidenceWithMMS->SetParameterName("mode", false);
    fCoincidenceWithMMS->AvailableForStates(G4State_Idle);

    fCoincidenceWithMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMCP", this);
    fCoincidenceWithMCP->SetGuidance("Coincidence with MCP if enabled.");
    fCoincidenceWithMCP->SetParameterName("mode", false);
    fCoincidenceWithMCP->AvailableForStates(G4State_Idle);

    fCoincidenceWithECal = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithECal", this);
    fCoincidenceWithECal->SetGuidance("Coincidence with ECal if enabled.");
    fCoincidenceWithECal->SetParameterName("mode", false);
    fCoincidenceWithECal->AvailableForStates(G4State_Idle);

    fSaveTTCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveTTCHitData", this);
    fSaveTTCHitData->SetGuidance("Save TTC hit data if enabled.");
    fSaveTTCHitData->SetParameterName("mode", false);
    fSaveTTCHitData->AvailableForStates(G4State_Idle);

    fSaveCDCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveCDCHitData", this);
    fSaveCDCHitData->SetGuidance("Save CDC hit data if enabled.");
    fSaveCDCHitData->SetParameterName("mode", false);
    fSaveCDCHitData->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSavePrimaryVertexData.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SavePrimaryVertexData(fSavePrimaryVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMMS.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMMS(fCoincidenceWithMMS->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMCP(fCoincidenceWithMCP->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithECal.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithECal(fCoincidenceWithECal->GetNewBoolValue(value));
        });
    } else if (command == fSaveTTCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveTTCHitData(fSaveTTCHitData->GetNewBoolValue(value));
        });
    } else if (command == fSaveCDCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveCDCHitData(fSaveCDCHitData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
