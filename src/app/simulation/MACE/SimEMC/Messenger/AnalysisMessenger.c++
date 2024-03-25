#include "MACE/SimEMC/Action/TrackingAction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimEMC::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fCoincidenceWithEMC{},
    fCoincidenceWithMCP{},
    fSaveDecayVertexData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimEMC::Analysis controller.");

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this);
    fFilePath->SetGuidance("Set file path.");
    fFilePath->SetParameterName("path", false);
    fFilePath->AvailableForStates(G4State_Idle);

    fFileMode = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileMode", this);
    fFileMode->SetGuidance("Set mode (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileMode->SetParameterName("mode", false);
    fFileMode->AvailableForStates(G4State_Idle);

    fCoincidenceWithEMC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithEMC", this);
    fCoincidenceWithEMC->SetGuidance("Enable EMC for coincident detection.");
    fCoincidenceWithEMC->SetParameterName("mode", false);
    fCoincidenceWithEMC->AvailableForStates(G4State_Idle);

    fCoincidenceWithMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMCP", this);
    fCoincidenceWithMCP->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fCoincidenceWithMCP->SetParameterName("mode", false);
    fCoincidenceWithMCP->AvailableForStates(G4State_Idle);

    fSaveDecayVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveDecayVertexData", this);
    fSaveDecayVertexData->SetGuidance("Do not save decay vertex data if disabled.");
    fSaveDecayVertexData->SetParameterName("mode", false);
    fSaveDecayVertexData->AvailableForStates(G4State_Idle);
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
    } else if (command == fCoincidenceWithEMC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithEMC(fCoincidenceWithEMC->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMCP(fCoincidenceWithMCP->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimEMC::inline Messenger
