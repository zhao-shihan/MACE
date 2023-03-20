#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    Singleton(),
    G4UImessenger(),
    fAnalysis(nullptr),
    fDirectory(),
    fResultPath(),
    fEnableYieldAnalysis() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimTarget::Analysis controller.");

    fResultPath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/ResultPath", this),
    fResultPath->SetGuidance("Set result name.");
    fResultPath->SetParameterName("result name", false);
    fResultPath->AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableYieldAnalysis", this),
    fEnableYieldAnalysis->SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis->SetParameterName("bool", false);
    fEnableYieldAnalysis->AvailableForStates(G4State_PreInit);
}

AnalysisMessenger::~AnalysisMessenger() = default;

void AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fResultPath.get()) {
        fAnalysis->ResultPath(std::string_view(value));
    } else if (command == fEnableYieldAnalysis.get()) {
        fAnalysis->EnableYieldAnalysis(fEnableYieldAnalysis->GetNewBoolValue(value));
    }
}

} // namespace MACE::SimTarget::inline Messenger
