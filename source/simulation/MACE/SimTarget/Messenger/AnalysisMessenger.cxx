#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimTarget::Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton<AnalysisMessenger>(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory(nullptr),
    fSetResultName(nullptr),
    fEnableYieldAnalysis(nullptr) {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimTarget::Analysis controller.");

    fSetResultName = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/SetResultName", this),
    fSetResultName->SetGuidance("Set result name.");
    fSetResultName->SetParameterName("result name", false);
    fSetResultName->AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableYieldAnalysis", this),
    fEnableYieldAnalysis->SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis->SetParameterName("bool", false);
    fEnableYieldAnalysis->AvailableForStates(G4State_PreInit);
}

AnalysisMessenger::~AnalysisMessenger() = default;

void AnalysisMessenger::SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) {
    if (command == fSetResultName.get()) {
        fAnalysis->SetResultName(value);
    } else if (command == fEnableYieldAnalysis.get()) {
        fAnalysis->EnableYieldAnalysis(fEnableYieldAnalysis->GetNewBoolValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
