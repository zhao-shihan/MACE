#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory(),
    fSetResultPath(),
    fEnableYieldAnalysis() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimTarget::Analysis controller.");

    fSetResultPath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/SetResultPath", this),
    fSetResultPath->SetGuidance("Set result name.");
    fSetResultPath->SetParameterName("result name", false);
    fSetResultPath->AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableYieldAnalysis", this),
    fEnableYieldAnalysis->SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis->SetParameterName("bool", false);
    fEnableYieldAnalysis->AvailableForStates(G4State_PreInit);
}

AnalysisMessenger::~AnalysisMessenger() = default;

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetResultPath.get()) {
        fAnalysis->SetResultPath(std::string_view(value));
    } else if (command == fEnableYieldAnalysis.get()) {
        fAnalysis->EnableYieldAnalysis(fEnableYieldAnalysis->GetNewBoolValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
