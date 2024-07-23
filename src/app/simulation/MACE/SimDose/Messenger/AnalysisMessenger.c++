#include "MACE/SimDose/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimDose/Analysis.h++"
#include "MACE/SimDose/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimDose::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fMapNBinX{},
    fMapXMin{},
    fMapXMax{},
    fMapNBinY{},
    fMapYMin{},
    fMapYMax{},
    fMapNBinZ{},
    fMapZMin{},
    fMapZMax{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimDose::Analysis controller.");

    fMapNBinX = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Analysis/MapNBinX", this);
    fMapNBinX->SetGuidance("Set bin parameter for result histograms.");
    fMapNBinX->SetParameterName("n", false);
    fMapNBinX->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapXMin = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapXMin", this);
    fMapXMin->SetGuidance("Set bin parameter for result histograms.");
    fMapXMin->SetParameterName("value", false);
    fMapXMin->SetUnitCategory("Length");
    fMapXMin->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapXMax = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapXMax", this);
    fMapXMax->SetGuidance("Set bin parameter for result histograms.");
    fMapXMax->SetParameterName("value", false);
    fMapXMax->SetUnitCategory("Length");
    fMapXMax->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapNBinY = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Analysis/MapNBinY", this);
    fMapNBinY->SetGuidance("Set bin parameter for result histograms.");
    fMapNBinY->SetParameterName("n", false);
    fMapNBinY->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapYMin = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapYMin", this);
    fMapYMin->SetGuidance("Set bin parameter for result histograms.");
    fMapYMin->SetParameterName("value", false);
    fMapYMin->SetUnitCategory("Length");
    fMapYMin->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapYMax = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapYMax", this);
    fMapYMax->SetGuidance("Set bin parameter for result histograms.");
    fMapYMax->SetParameterName("value", false);
    fMapYMax->SetUnitCategory("Length");
    fMapYMax->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapNBinZ = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Analysis/MapNBinZ", this);
    fMapNBinZ->SetGuidance("Set bin parameter for result histograms.");
    fMapNBinZ->SetParameterName("n", false);
    fMapNBinZ->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapZMin = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapZMin", this);
    fMapZMin->SetGuidance("Set bin parameter for result histograms.");
    fMapZMin->SetParameterName("value", false);
    fMapZMin->SetUnitCategory("Length");
    fMapZMin->AvailableForStates(G4State_PreInit, G4State_Idle);

    fMapZMax = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Analysis/MapZMax", this);
    fMapZMax->SetGuidance("Set bin parameter for result histograms.");
    fMapZMax->SetParameterName("value", false);
    fMapZMax->SetUnitCategory("Length");
    fMapZMax->AvailableForStates(G4State_PreInit, G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMapNBinX.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapNBinX(fMapNBinX->GetNewIntValue(value));
        });
    } else if (command == fMapXMin.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapXMin(fMapXMin->GetNewDoubleValue(value));
        });
    } else if (command == fMapXMax.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapXMax(fMapXMax->GetNewDoubleValue(value));
        });
    } else if (command == fMapNBinY.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapNBinY(fMapNBinY->GetNewIntValue(value));
        });
    } else if (command == fMapYMin.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapYMin(fMapYMin->GetNewDoubleValue(value));
        });
    } else if (command == fMapYMax.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapYMax(fMapYMax->GetNewDoubleValue(value));
        });
    } else if (command == fMapNBinZ.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapNBinZ(fMapNBinZ->GetNewIntValue(value));
        });
    } else if (command == fMapZMin.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapZMin(fMapZMin->GetNewDoubleValue(value));
        });
    } else if (command == fMapZMax.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.MapZMax(fMapZMax->GetNewDoubleValue(value));
        });
    }
}

} // namespace MACE::SimDose::inline Messenger
