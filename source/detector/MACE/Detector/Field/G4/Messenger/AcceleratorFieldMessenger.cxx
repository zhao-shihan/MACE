#include "MACE/Detector/Description/AcceleratorField.hxx"
#include "MACE/Detector/Field/G4/AcceleratorField.hxx"
#include "MACE/Detector/Field/G4/Messenger/AcceleratorFieldMessenger.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::Detector::Field::G4::inline Messenger {

AcceleratorFieldMessenger::AcceleratorFieldMessenger() :
    Singleton(),
    G4UImessenger(),
    fAcceleratorField(nullptr),
    fDirectory(),
    fAcceleratorPotential() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fAcceleratorPotential = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/AcceleratorPotential", this);
    fAcceleratorPotential->SetGuidance("Set accelerator electric potential.");
    fAcceleratorPotential->SetParameterName("V", false);
    fAcceleratorPotential->SetUnitCategory("Electric potential");
    fAcceleratorPotential->AvailableForStates(G4State_Idle);
}

AcceleratorFieldMessenger::~AcceleratorFieldMessenger() = default;

void AcceleratorFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fAcceleratorPotential.get()) {
        Description::AcceleratorField::Instance().AcceleratorPotential(fAcceleratorPotential->GetNewDoubleValue(value));
    }
}

} // namespace MACE::Detector::Field::G4::inline Messenger
