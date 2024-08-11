#include "MACE/SimECal/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimECal/Action/TrackingAction.h++"
#include "MACE/SimECal/Analysis.h++"
#include "MACE/SimECal/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimECal::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fSavePrimaryVertexData{},
    fSaveDecayVertexData{},
    fCoincidenceWithECal{},
    fCoincidenceWithMCP{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimECal::Analysis controller.");

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

    fCoincidenceWithECal = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithECal", this);
    fCoincidenceWithECal->SetGuidance("Enable ECal for coincident detection.");
    fCoincidenceWithECal->SetParameterName("mode", false);
    fCoincidenceWithECal->AvailableForStates(G4State_Idle);

    fCoincidenceWithMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMCP", this);
    fCoincidenceWithMCP->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fCoincidenceWithMCP->SetParameterName("mode", false);
    fCoincidenceWithMCP->AvailableForStates(G4State_Idle);
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
    } else if (command == fCoincidenceWithECal.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithECal(fCoincidenceWithECal->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMCP(fCoincidenceWithMCP->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimECal::inline Messenger
