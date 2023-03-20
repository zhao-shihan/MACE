#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMACE::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory(),
    fEnableCoincidenceOfEMCal(),
    fEnableCoincidenceOfMCP(),
    fResultPath() {

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

    fResultPath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/ResultPath", this);
    fResultPath->SetGuidance("Set file name.");
    fResultPath->SetParameterName("file name", false);
    fResultPath->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fEnableCoincidenceOfEMCal.get()) {
        fAnalysis->EnableCoincidenceOfEMCal(fEnableCoincidenceOfEMCal->GetNewBoolValue(value));
    } else if (command == fEnableCoincidenceOfMCP.get()) {
        fAnalysis->EnableCoincidenceOfMCP(fEnableCoincidenceOfMCP->GetNewBoolValue(value));
    } else if (command == fResultPath.get()) {
        fAnalysis->ResultPath(std::string_view(value));
    }
}

} // namespace MACE::SimMACE::inline Messenger
