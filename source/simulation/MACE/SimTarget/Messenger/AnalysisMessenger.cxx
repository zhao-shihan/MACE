#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"

namespace MACE::SimTarget::Messenger {

using MACE::SimTarget::Analysis;

AnalysisMessenger& AnalysisMessenger::Instance() {
    static AnalysisMessenger instance;
    return instance;
}

AnalysisMessenger::AnalysisMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Analysis/"),
    fSetResultName("/MACE/Analysis/SetResultName", this),
    fEnableYieldAnalysis("/MACE/Analysis/EnableYieldAnalysis", this),
    fSetDetectableRegion("/MACE/Analysis/SetDetectableRegion", this) {

    fDirectory.SetGuidance("MACE::SimTarget::Analysis controller.");

    fSetResultName.SetGuidance("Set result name.");
    fSetResultName.SetParameterName("result name", false);
    fSetResultName.AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis.SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis.SetParameterName("bool", false);
    fEnableYieldAnalysis.AvailableForStates(G4State_PreInit);

    fSetDetectableRegion.SetGuidance("Set boolean expression to represent the region where the muonium decay is detectable. Where the expression evaluate to true is the region.");
    fSetDetectableRegion.SetParameterName("expr", false);
    fSetDetectableRegion.AvailableForStates(G4State_PreInit);
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    auto&& analysis = Analysis::Instance();
    if (command == std::addressof(fSetResultName)) {
        analysis.SetResultName(value);
    } else if (command == std::addressof(fEnableYieldAnalysis)) {
        analysis.EnableYieldAnalysis(fEnableYieldAnalysis.GetNewBoolValue(value));
    } else if (command == std::addressof(fSetDetectableRegion)) {
        analysis.SetDetectableRegion(value);
    }
}

} // namespace MACE::SimTarget::Messenger
