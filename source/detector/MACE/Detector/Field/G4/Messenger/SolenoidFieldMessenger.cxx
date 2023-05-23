#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.hxx"
#include "MACE/Detector/Field/G4/SolenoidB1Field.hxx"
#include "MACE/Detector/Field/G4/SolenoidB2Field.hxx"
#include "MACE/Detector/Field/G4/SolenoidS1Field.hxx"
#include "MACE/Detector/Field/G4/SolenoidS2Field.hxx"
#include "MACE/Detector/Field/G4/SolenoidS3Field.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::Detector::Field::G4::inline Messenger {

SolenoidFieldMessenger::SolenoidFieldMessenger() :
    Singleton(),
    G4UImessenger(),
    fSolenoidB1Field(nullptr),
    fSolenoidB2Field(nullptr),
    fSolenoidS1Field(nullptr),
    fSolenoidS2Field(nullptr),
    fSolenoidS3Field(nullptr),
    fDirectory(),
    fSolenoidMagneticField() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSolenoidMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SolenoidMagneticField", this);
    fSolenoidMagneticField->SetGuidance("Set the magnetic flux density of solenoid magnetic field.");
    fSolenoidMagneticField->SetParameterName("B", false);
    fSolenoidMagneticField->SetUnitCategory("Magnetic flux density");
    fSolenoidMagneticField->AvailableForStates(G4State_Idle);
}

SolenoidFieldMessenger::~SolenoidFieldMessenger() = default;

void SolenoidFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSolenoidMagneticField.get()) {
        Description::Solenoid::Instance().MagneticFluxDensity(fSolenoidMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::Detector::Field::G4::inline Messenger
