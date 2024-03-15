#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Simulation/Field/EMCField.h++"
#include "MACE/Simulation/Field/EMCFieldMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

EMCFieldMessenger::EMCFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSpectrometerMagneticField{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSpectrometerMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/EMCMagneticField", this);
    fSpectrometerMagneticField->SetGuidance("Set the magnetic flux density of spectrometer magnetic field.");
    fSpectrometerMagneticField->SetParameterName("B", false);
    fSpectrometerMagneticField->SetUnitCategory("Magnetic flux density");
    fSpectrometerMagneticField->AvailableForStates(G4State_Idle);
}

EMCFieldMessenger::~EMCFieldMessenger() = default;

auto EMCFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSpectrometerMagneticField.get()) {
        Detector::Description::EMCField::Instance().MagneticFluxDensity(fSpectrometerMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
