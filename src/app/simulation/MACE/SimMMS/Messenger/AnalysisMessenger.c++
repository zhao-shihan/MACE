#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMMS::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fFilePath{},
    fFileMode{},
    fCoincidenceWithCDC{},
    fCoincidenceWithSTC{},
    fSaveCDCHitData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMMS::Analysis controller.");

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
    } else if (command == fSaveCDCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveCDCHitData(fSaveCDCHitData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMMS::inline Messenger
