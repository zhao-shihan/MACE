#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Simulation/Field/MMSFieldMessenger.h++"
#include "MACE/Simulation/Field/MMSField.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

MMSFieldMessenger::MMSFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fMMSMagneticField{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fMMSMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/MMSMagneticField", this);
    fMMSMagneticField->SetGuidance("Set the magnetic flux density of mms magnetic field.");
    fMMSMagneticField->SetParameterName("B", false);
    fMMSMagneticField->SetUnitCategory("Magnetic flux density");
    fMMSMagneticField->AvailableForStates(G4State_Idle);
}

MMSFieldMessenger::~MMSFieldMessenger() = default;

auto MMSFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMMSMagneticField.get()) {
        Detector::Description::MMSField::Instance().MagneticFluxDensity(fMMSMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
