#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Field/G4/AcceleratorField.h++"
#include "MACE/Detector/Field/G4/Messenger/AcceleratorFieldMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::Detector::Field::G4::inline Messenger {

AcceleratorFieldMessenger::AcceleratorFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fAcceleratorPotential{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fAcceleratorPotential = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/AcceleratorPotential", this);
    fAcceleratorPotential->SetGuidance("Set accelerator electric potential.");
    fAcceleratorPotential->SetParameterName("V", false);
    fAcceleratorPotential->SetUnitCategory("Electric potential");
    fAcceleratorPotential->AvailableForStates(G4State_Idle);
}

AcceleratorFieldMessenger::~AcceleratorFieldMessenger() = default;

auto AcceleratorFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fAcceleratorPotential.get()) {
        Description::AcceleratorField::Instance().AcceleratorPotential(fAcceleratorPotential->GetNewDoubleValue(value));
    }
}

} // namespace MACE::Detector::Field::G4::inline Messenger
