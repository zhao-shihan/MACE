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
    fEnableCoincidenceOfEMC{},
    fEnableCoincidenceOfMCP{} {

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

    fEnableCoincidenceOfEMC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfEMC", this);
    fEnableCoincidenceOfEMC->SetGuidance("Enable EMC for coincident detection.");
    fEnableCoincidenceOfEMC->SetParameterName("mode", false);
    fEnableCoincidenceOfEMC->AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfMCP", this);
    fEnableCoincidenceOfMCP->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfMCP->SetParameterName("mode", false);
    fEnableCoincidenceOfMCP->AvailableForStates(G4State_Idle);
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
    } else if (command == fEnableCoincidenceOfEMC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.EnableCoincidenceOfEMC(fEnableCoincidenceOfEMC->GetNewBoolValue(value));
        });
    } else if (command == fEnableCoincidenceOfMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.EnableCoincidenceOfMCP(fEnableCoincidenceOfMCP->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimEMC::inline Messenger
