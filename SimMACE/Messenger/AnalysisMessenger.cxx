#include "G4UIdirectory.hh"

#include "SimMACE/Messenger/AnalysisMessenger.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Messenger;

AnalysisMessenger* AnalysisMessenger::Instance() {
    static AnalysisMessenger instance;
    return &instance;
}

AnalysisMessenger::AnalysisMessenger() :
    G4UImessenger(),
    fpAnalysis(nullptr) {

    fDirectory = new G4UIdirectory("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMACE::Analysis controller.");

    fEnableCoincidenceOfCalorimeter = new G4UIcmdWithABool("/MACE/Analysis/EnableCoincidenceOfCalorimeter", this);
    fEnableCoincidenceOfCalorimeter->SetGuidance("Enable calorimeter for coincident detection.");
    fEnableCoincidenceOfCalorimeter->SetParameterName("mode", false);
    fEnableCoincidenceOfCalorimeter->AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfVertexDetector = new G4UIcmdWithABool("/MACE/Analysis/EnableCoincidenceOfVertexDetector", this);
    fEnableCoincidenceOfVertexDetector->SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfVertexDetector->SetParameterName("mode", false);
    fEnableCoincidenceOfVertexDetector->AvailableForStates(G4State_Idle);

    fSetFileName = new G4UIcmdWithAString("/MACE/Analysis/SetFileName", this);
    fSetFileName->SetGuidance("Set file name.");
    fSetFileName->SetParameterName("file name", false);
    fSetFileName->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() {
    delete fEnableCoincidenceOfCalorimeter;
    delete fEnableCoincidenceOfVertexDetector;
    delete fSetFileName;
    delete fDirectory;
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fEnableCoincidenceOfCalorimeter) {
        fpAnalysis->SetEnableCoincidenceOfCalorimeter(fEnableCoincidenceOfCalorimeter->GetNewBoolValue(value));
    } else if (command == fEnableCoincidenceOfVertexDetector) {
        fpAnalysis->SetEnableCoincidenceOfVertexDetector(fEnableCoincidenceOfVertexDetector->GetNewBoolValue(value));
    } else if (command == fSetFileName) {
        fpAnalysis->SetFileName(value);
    }
}
