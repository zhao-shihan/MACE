#include "MACE/Simulation/SimTarget/Analysis.hxx"
#include "MACE/Simulation/SimTarget/Messenger/AnalysisMessenger.hxx"

#include "G4UIdirectory.hh"

namespace MACE::Simulation::SimTarget::Messenger {

using MACE::Simulation::SimTarget::Analysis;

AnalysisMessenger& AnalysisMessenger::Instance() {
    static AnalysisMessenger instance;
    return instance;
}

AnalysisMessenger::AnalysisMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Analysis/"),
    fSetResultName("/MACE/Analysis/SetResultName", this),
    fMergeResult("/MACE/Analysis/MergeResult", this) {

    fDirectory.SetGuidance("MACE::Simulation::SimTarget::Analysis controller.");

    fSetResultName.SetGuidance("Set result name.");
    fSetResultName.SetParameterName("result name", false);
    fSetResultName.AvailableForStates(G4State_PreInit);

    fMergeResult.SetGuidance("Merge result after MPI execution.");
    fMergeResult.SetParameterName("forced", true);
    fMergeResult.SetDefaultValue(false);
    fMergeResult.AvailableForStates(G4State_Idle);
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    auto&& analysis = Analysis::Instance();
    if (command == std::addressof(fSetResultName)) {
        analysis.SetResultName(value);
    } else if (command == std::addressof(fMergeResult)) {
        analysis.Merge(fMergeResult.GetNewBoolValue(value));
    }
}

} // namespace MACE::Simulation::SimTarget::Messenger
