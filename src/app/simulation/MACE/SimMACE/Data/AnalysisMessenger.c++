#include "MACE/SimMACE/Data/Analysis.h++"
#include "MACE/SimMACE/Data/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMACE::Data {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fCoincidenceWithCDC{},
    fCoincidenceWithSTC{},
    fCoincidenceWithMCP{},
    fCoincidenceWithEMC{},
    fSaveCDCHitData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMACE::Data::Analysis controller.");

    fFilePath = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FilePath", this);
    fFilePath->SetGuidance("Set file path.");
    fFilePath->SetParameterName("path", false);
    fFilePath->AvailableForStates(G4State_Idle);

    fFileMode = std::make_unique<G4UIcmdWithAString>("/MACE/Analysis/FileMode", this);
    fFileMode->SetGuidance("Set mode (NEW, RECREATE, or UPDATE) for opening ROOT file(s).");
    fFileMode->SetParameterName("mode", false);
    fFileMode->AvailableForStates(G4State_Idle);

    fCoincidenceWithCDC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithCDC", this);
    fCoincidenceWithCDC->SetGuidance("Coincidence with CDC if enabled.");
    fCoincidenceWithCDC->SetParameterName("mode", false);
    fCoincidenceWithCDC->AvailableForStates(G4State_Idle);

    fCoincidenceWithSTC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithSTC", this);
    fCoincidenceWithSTC->SetGuidance("Coincidence with STC if enabled.");
    fCoincidenceWithSTC->SetParameterName("mode", false);
    fCoincidenceWithSTC->AvailableForStates(G4State_Idle);

    fCoincidenceWithMCP = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithMCP", this);
    fCoincidenceWithMCP->SetGuidance("Coincidence with MCP if enabled.");
    fCoincidenceWithMCP->SetParameterName("mode", false);
    fCoincidenceWithMCP->AvailableForStates(G4State_Idle);

    fCoincidenceWithEMC = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/CoincidenceWithEMC", this);
    fCoincidenceWithEMC->SetGuidance("Coincidence with EMC if enabled.");
    fCoincidenceWithEMC->SetParameterName("mode", false);
    fCoincidenceWithEMC->AvailableForStates(G4State_Idle);

    fSaveCDCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveCDCHitData", this);
    fSaveCDCHitData->SetGuidance("Do not save CDC hit data if disabled.");
    fSaveCDCHitData->SetParameterName("mode", false);
    fSaveCDCHitData->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fFilePath.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FilePath(std::string_view(value));
        });
    } else if (command == fFileMode.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.FileMode(value);
        });
    } else if (command == fCoincidenceWithCDC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithCDC(fCoincidenceWithCDC->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithSTC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithSTC(fCoincidenceWithSTC->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithMCP.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithMCP(fCoincidenceWithMCP->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithEMC.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithEMC(fCoincidenceWithEMC->GetNewBoolValue(value));
        });
    } else if (command == fSaveCDCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveCDCHitData(fSaveCDCHitData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMACE::Data
