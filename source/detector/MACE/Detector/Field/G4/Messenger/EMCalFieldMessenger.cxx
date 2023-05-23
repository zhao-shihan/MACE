#include "MACE/Detector/Description/EMCalField.hxx"
#include "MACE/Detector/Field/G4/Messenger/EMCalFieldMessenger.hxx"
#include "MACE/Detector/Field/G4/EMCalField.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::Detector::Field::G4::inline Messenger {

EMCalFieldMessenger::EMCalFieldMessenger() :
    Singleton(),
    G4UImessenger(),
    fEMCalField(nullptr),
    fDirectory(),
    fSpectrometerMagneticField() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSpectrometerMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/EMCalMagneticField", this);
    fSpectrometerMagneticField->SetGuidance("Set the magnetic flux density of spectrometer magnetic field.");
    fSpectrometerMagneticField->SetParameterName("B", false);
    fSpectrometerMagneticField->SetUnitCategory("Magnetic flux density");
    fSpectrometerMagneticField->AvailableForStates(G4State_Idle);
}

EMCalFieldMessenger::~EMCalFieldMessenger() = default;

void EMCalFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSpectrometerMagneticField.get()) {
        Description::EMCalField::Instance().MagneticFluxDensity(fSpectrometerMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::Detector::Field::G4::inline Messenger
