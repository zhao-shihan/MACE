#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Simulation/Field/EMCField.h++"
#include "MACE/Simulation/Field/EMCFieldMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

EMCFieldMessenger::EMCFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fEMCMagneticField{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fEMCMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/EMCMagneticField", this);
    fEMCMagneticField->SetGuidance("Set the magnetic flux density of mms magnetic field.");
    fEMCMagneticField->SetParameterName("B", false);
    fEMCMagneticField->SetUnitCategory("Magnetic flux density");
    fEMCMagneticField->AvailableForStates(G4State_Idle);
}

EMCFieldMessenger::~EMCFieldMessenger() = default;

auto EMCFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fEMCMagneticField.get()) {
        Detector::Description::EMCField::Instance().MagneticFluxDensity(fEMCMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
