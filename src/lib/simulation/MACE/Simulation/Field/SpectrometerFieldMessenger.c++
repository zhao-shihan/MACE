#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Simulation/Field/SpectrometerFieldMessenger.h++"
#include "MACE/Simulation/Field/SpectrometerField.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

SpectrometerFieldMessenger::SpectrometerFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSpectrometerMagneticField{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSpectrometerMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SpectrometerMagneticField", this);
    fSpectrometerMagneticField->SetGuidance("Set the magnetic flux density of spectrometer magnetic field.");
    fSpectrometerMagneticField->SetParameterName("B", false);
    fSpectrometerMagneticField->SetUnitCategory("Magnetic flux density");
    fSpectrometerMagneticField->AvailableForStates(G4State_Idle);
}

SpectrometerFieldMessenger::~SpectrometerFieldMessenger() = default;

auto SpectrometerFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSpectrometerMagneticField.get()) {
        Detector::Description::SpectrometerField::Instance().MagneticFluxDensity(fSpectrometerMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
