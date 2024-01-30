#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimEMC::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton{},
    G4UImessenger{},
    fAnalysis{nullptr},
    fDirectory{},
    fEnableCoincidenceOfEMC{},
    fEnableCoincidenceOfMCP{},
    fFilePath{},
    fFileOption{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimEMC::Analysis controller.");

    fEnableCoincidenceOfEMC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfEMC", this);
    fEnableCoincidenceOfEMC->SetGuidance("Enable EMC for coincident detection.");
    fEnableCoincidenceOfEMC->SetParameterName("mode", false);
    fEnableCoincidenceOfEMC->AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfMCP", this);
    fEnableCoincidenceOfMCP->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfMCP->SetParameterName("mode", false);
    fEnableCoincidenceOfMCP->AvailableForStates(G4State_Idle);

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this);
    fFilePath->SetGuidance("Set file name.");
    fFilePath->SetParameterName("file name", false);
    fFilePath->AvailableForStates(G4State_Idle);

    fFileOption = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileOption", this);
    fFileOption->SetGuidance("Set option (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileOption->SetParameterName("option", false);
    fFileOption->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fEnableCoincidenceOfEMC.get()) {
        fAnalysis->EnableCoincidenceOfEMC(fEnableCoincidenceOfEMC->GetNewBoolValue(value));
    } else if (command == fEnableCoincidenceOfMCP.get()) {
        fAnalysis->EnableCoincidenceOfMCP(fEnableCoincidenceOfMCP->GetNewBoolValue(value));
    } else if (command == fFilePath.get()) {
        fAnalysis->FilePath(std::string_view(value));
    } else if (command == fFileOption.get()) {
        fAnalysis->FileOption(value);
    }
}

} // namespace MACE::SimEMC::inline Messenger
