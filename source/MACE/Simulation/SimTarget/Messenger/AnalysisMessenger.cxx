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
    fEnableYieldAnalysis("/MACE/Analysis/EnableYieldAnalysis", this) {

    fDirectory.SetGuidance("MACE::Simulation::SimTarget::Analysis controller.");

    fSetResultName.SetGuidance("Set result name.");
    fSetResultName.SetParameterName("result name", false);
    fSetResultName.AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis.SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis.SetParameterName("bool", false);
    fEnableYieldAnalysis.AvailableForStates(G4State_PreInit);
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    auto&& analysis = Analysis::Instance();
    if (command == std::addressof(fSetResultName)) {
        analysis.SetResultName(value);
    } else if (command == std::addressof(fEnableYieldAnalysis)) {
        analysis.EnableYieldAnalysis(fEnableYieldAnalysis.GetNewBoolValue(value));
    }
}

} // namespace MACE::Simulation::SimTarget::Messenger
