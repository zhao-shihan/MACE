#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Field/G4/Messenger/SpectrometerFieldMessenger.h++"
#include "MACE/Detector/Field/G4/SpectrometerField.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::Detector::Field::G4::inline Messenger {

SpectrometerFieldMessenger::SpectrometerFieldMessenger() :
    Singleton(),
    G4UImessenger(),
    fSpectrometerField(nullptr),
    fDirectory(),
    fSpectrometerMagneticField() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSpectrometerMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SpectrometerMagneticField", this);
    fSpectrometerMagneticField->SetGuidance("Set the magnetic flux density of spectrometer magnetic field.");
    fSpectrometerMagneticField->SetParameterName("B", false);
    fSpectrometerMagneticField->SetUnitCategory("Magnetic flux density");
    fSpectrometerMagneticField->AvailableForStates(G4State_Idle);
}

SpectrometerFieldMessenger::~SpectrometerFieldMessenger() = default;

void SpectrometerFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSpectrometerMagneticField.get()) {
        Description::SpectrometerField::Instance().MagneticFluxDensity(fSpectrometerMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::Detector::Field::G4::inline Messenger
