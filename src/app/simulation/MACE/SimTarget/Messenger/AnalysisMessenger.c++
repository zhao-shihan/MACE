#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fEnableYieldAnalysis{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimTarget::Analysis controller.");

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this),
    fFilePath->SetGuidance("Set file path.");
    fFilePath->SetParameterName("path", false);
    fFilePath->AvailableForStates(G4State_PreInit);

    fFileMode = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileMode", this);
    fFileMode->SetGuidance("Set mode (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileMode->SetParameterName("mode", false);
    fFileMode->AvailableForStates(G4State_PreInit);

    fEnableYieldAnalysis = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/EnableYieldAnalysis", this),
    fEnableYieldAnalysis->SetGuidance("Enable auto analysis of yield.");
    fEnableYieldAnalysis->SetParameterName("bool", false);
    fEnableYieldAnalysis->AvailableForStates(G4State_PreInit);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fFilePath.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FilePath(std::string_view{value});
        });
    } else if (command == fFileMode.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FileMode(value);
        });
    } else if (command == fEnableYieldAnalysis.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.EnableYieldAnalysis(fEnableYieldAnalysis->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimTarget::inline Messenger
