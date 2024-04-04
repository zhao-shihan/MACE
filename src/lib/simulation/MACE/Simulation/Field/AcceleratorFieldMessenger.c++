#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Simulation/Field/AcceleratorField.h++"
#include "MACE/Simulation/Field/AcceleratorFieldMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

AcceleratorFieldMessenger::AcceleratorFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fAcceleratePotential{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fAcceleratePotential = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/AcceleratePotential", this);
    fAcceleratePotential->SetGuidance("Set accelerator electric potential.");
    fAcceleratePotential->SetParameterName("V", false);
    fAcceleratePotential->SetUnitCategory("Electric potential");
    fAcceleratePotential->AvailableForStates(G4State_Idle);
}

AcceleratorFieldMessenger::~AcceleratorFieldMessenger() = default;

auto AcceleratorFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fAcceleratePotential.get()) {
        Detector::Description::Accelerator::Instance().AcceleratePotential(fAcceleratePotential->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
