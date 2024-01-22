#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMACE::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fCoincidenceWithCDC{},
    fCoincidenceWithMCP{},
    fCoincidenceWithEMC{},
    fFilePath{},
    fFileOption{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMACE::Analysis controller.");

    fCoincidenceWithCDC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithCDC", this);
    fCoincidenceWithCDC->SetGuidance("Coincidence with CDC if enabled.");
    fCoincidenceWithCDC->SetParameterName("mode", false);
    fCoincidenceWithCDC->AvailableForStates(G4State_Idle);

    fCoincidenceWithMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMCP", this);
    fCoincidenceWithMCP->SetGuidance("Coincidence with MCP if enabled.");
    fCoincidenceWithMCP->SetParameterName("mode", false);
    fCoincidenceWithMCP->AvailableForStates(G4State_Idle);

    fCoincidenceWithEMC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithEMC", this);
    fCoincidenceWithEMC->SetGuidance("Coincidence with EMC if enabled.");
    fCoincidenceWithEMC->SetParameterName("mode", false);
    fCoincidenceWithEMC->AvailableForStates(G4State_Idle);

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this);
    fFilePath->SetGuidance("Set file name.");
    fFilePath->SetParameterName("file name", false);
    fFilePath->AvailableForStates(G4State_Idle);

    fFileOption = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileOption", this);
    fFileOption->SetGuidance("Set option (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileOption->SetParameterName("option", false);
    fFileOption->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fCoincidenceWithCDC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithCDC(fCoincidenceWithCDC->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMCP(fCoincidenceWithMCP->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithEMC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithEMC(fCoincidenceWithEMC->GetNewBoolValue(value));
        });
    } else if (command == fFilePath.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FilePath(std::string_view(value));
        });
    } else if (command == fFileOption.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FileOption(value);
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
