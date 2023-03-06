#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMACE::Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory(),
    fEnableCoincidenceOfEMCal(),
    fEnableCoincidenceOfMCP(),
    fSetResultPath() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMACE::Analysis controller.");

    fEnableCoincidenceOfEMCal = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfEMCal", this);
    fEnableCoincidenceOfEMCal->SetGuidance("Enable EMCal for coincident detection.");
    fEnableCoincidenceOfEMCal->SetParameterName("mode", false);
    fEnableCoincidenceOfEMCal->AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableCoincidenceOfMCP", this);
    fEnableCoincidenceOfMCP->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfMCP->SetParameterName("mode", false);
    fEnableCoincidenceOfMCP->AvailableForStates(G4State_Idle);

    fSetResultPath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/SetResultPath", this);
    fSetResultPath->SetGuidance("Set file name.");
    fSetResultPath->SetParameterName("file name", false);
    fSetResultPath->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fEnableCoincidenceOfEMCal.get()) {
        fAnalysis->SetEnableCoincidenceOfEMCal(fEnableCoincidenceOfEMCal->GetNewBoolValue(value));
    } else if (command == fEnableCoincidenceOfMCP.get()) {
        fAnalysis->SetEnableCoincidenceOfMCP(fEnableCoincidenceOfMCP->GetNewBoolValue(value));
    } else if (command == fSetResultPath.get()) {
        fAnalysis->SetResultPath(std::string_view(value));
    }
}

} // namespace MACE::SimMACE::Messenger
