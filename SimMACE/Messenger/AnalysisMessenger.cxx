#include "G4UIdirectory.hh"

#include "SimMACE/Messenger/AnalysisMessenger.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Messenger;

AnalysisMessenger& AnalysisMessenger::Instance() {
    static AnalysisMessenger instance;
    return instance;
}

AnalysisMessenger::AnalysisMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Analysis/"),
    fEnableCoincidenceOfCalorimeter("/MACE/Analysis/EnableCoincidenceOfCalorimeter", this),
    fEnableCoincidenceOfVertexDetector("/MACE/Analysis/EnableCoincidenceOfVertexDetector", this),
    fSetResultName("/MACE/Analysis/SetResultName", this),
    fMergeResult("/MACE/Analysis/MergeResult", this) {

    fDirectory.SetGuidance("MACE::SimMACE::Analysis controller.");

    fEnableCoincidenceOfCalorimeter.SetGuidance("Enable calorimeter for coincident detection.");
    fEnableCoincidenceOfCalorimeter.SetParameterName("mode", false);
    fEnableCoincidenceOfCalorimeter.AvailableForStates(G4State_Idle);

    fEnableCoincidenceOfVertexDetector.SetGuidance("Enable atomic shell e-/e+ detector (typically MCP currently) for coincident detection.");
    fEnableCoincidenceOfVertexDetector.SetParameterName("mode", false);
    fEnableCoincidenceOfVertexDetector.AvailableForStates(G4State_Idle);

    fSetResultName.SetGuidance("Set file name.");
    fSetResultName.SetParameterName("file name", false);
    fSetResultName.AvailableForStates(G4State_Idle);

    fMergeResult.SetGuidance("Merge result after MPI execution.");
    fMergeResult.SetParameterName("forced", true);
    fMergeResult.SetDefaultValue(false);
    fMergeResult.AvailableForStates(G4State_Idle);
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    auto&& analysis = Analysis::Instance();
    if (command == std::addressof(fEnableCoincidenceOfCalorimeter)) {
        analysis.SetEnableCoincidenceOfCalorimeter(fEnableCoincidenceOfCalorimeter.GetNewBoolValue(value));
    } else if (command == std::addressof(fEnableCoincidenceOfVertexDetector)) {
        analysis.SetEnableCoincidenceOfVertexDetector(fEnableCoincidenceOfVertexDetector.GetNewBoolValue(value));
    } else if (command == std::addressof(fSetResultName)) {
        analysis.SetResultName(value);
    } else if (command = std::addressof(fMergeResult)) {
        analysis.Merge(fMergeResult.GetNewBoolValue(value));
    }
}
