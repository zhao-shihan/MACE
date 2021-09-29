#include "G4UIdirectory.hh"

#include "messenger/AnalysisMessenger.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

AnalysisMessenger* AnalysisMessenger::Instance() {
    static AnalysisMessenger instance;
    return &instance;
}

AnalysisMessenger::AnalysisMessenger() :
    G4UImessenger(),
    fpAnalysis(nullptr) {

    fDirectory = new G4UIdirectory("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimG4::Analysis controller.");

    fEnableCoincidenceOfCalorimeter = new G4UIcmdWithABool("/MACE/Analysis/EnableCoincidenceOfCalorimeter", this);
    fEnableCoincidenceOfCalorimeter->SetGuidance("Decide whether to enable the coincidence detection of the calorimeter. "
        "If true, save the event only when the orbital detector, magnetic spectrometer, and calorimeter are all coincident. "
        "Otherwise, the event will be saved once the orbital detector and the magnetic spectrometer are coincident. "
        "It is automatically set to true when detecting anti-muonium, and automatically set to false when detecting muonium. "
        "(See also /MACE/Setup/DetectionMode)");
    fEnableCoincidenceOfCalorimeter->SetParameterName("mode", false);
    fEnableCoincidenceOfCalorimeter->AvailableForStates(G4State_Idle);

    fSetFileName = new G4UIcmdWithAString("/MACE/Analysis/SetFileName", this);
    fSetFileName->SetGuidance("Set file name.");
    fSetFileName->SetParameterName("file name", false);
    fSetFileName->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() {
    delete fEnableCoincidenceOfCalorimeter;
    delete fSetFileName;
    delete fDirectory;
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fEnableCoincidenceOfCalorimeter) {
        fpAnalysis->SetEnableCoincidenceOfCalorimeter(fEnableCoincidenceOfCalorimeter->GetNewBoolValue(value));
    } else if (command == fSetFileName) {
        fpAnalysis->SetFileName(value);
    }
}
