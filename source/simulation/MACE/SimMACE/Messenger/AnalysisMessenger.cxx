#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"

namespace MACE::SimMACE::Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Environment::Resource::Singleton<AnalysisMessenger>(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory("/MACE/Analysis/"),
    fEnableCoincidenceOfEMCal("/MACE/Analysis/EnableCoincidenceOfEMCal", this),
    fEnableCoincidenceOfMCP("/MACE/Analysis/EnableCoincidenceOfMCP", this),
    fSetResultName("/MACE/Analysis/SetResultName", this) {

    fDirectory.SetGuidance("MACE::SimMACE::Analysis controller.");

    fEnableCoincidenceOfEMCal.SetGuidance("Enable EMCal for coincident detection.");
    fEnableCoincidenceOfEMCal.SetParameterName("mode", false);
    fEnableCoincidenceOfEMCal.AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfMCP.SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfMCP.SetParameterName("mode", false);
    fEnableCoincidenceOfMCP.AvailableForStates(G4State_Idle);

    fSetResultName.SetGuidance("Set file name.");
    fSetResultName.SetParameterName("file name", false);
    fSetResultName.AvailableForStates(G4State_Idle);
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fEnableCoincidenceOfEMCal)) {
        fAnalysis->SetEnableCoincidenceOfEMCal(fEnableCoincidenceOfEMCal.GetNewBoolValue(value));
    } else if (command == std::addressof(fEnableCoincidenceOfMCP)) {
        fAnalysis->SetEnableCoincidenceOfMCP(fEnableCoincidenceOfMCP.GetNewBoolValue(value));
    } else if (command == std::addressof(fSetResultName)) {
        fAnalysis->SetResultName(value);
    }
}

} // namespace MACE::SimMACE::Messenger
