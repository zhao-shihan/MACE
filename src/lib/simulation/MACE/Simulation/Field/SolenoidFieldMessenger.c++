#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidB1Field.h++"
#include "MACE/Simulation/Field/SolenoidB2Field.h++"
#include "MACE/Simulation/Field/SolenoidS1Field.h++"
#include "MACE/Simulation/Field/SolenoidS2Field.h++"
#include "MACE/Simulation/Field/SolenoidS3Field.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldMessenger::SolenoidFieldMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSolenoidMagneticField{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSolenoidMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SolenoidMagneticField", this);
    fSolenoidMagneticField->SetGuidance("Set the magnetic flux density of solenoid magnetic field.");
    fSolenoidMagneticField->SetParameterName("B", false);
    fSolenoidMagneticField->SetUnitCategory("Magnetic flux density");
    fSolenoidMagneticField->AvailableForStates(G4State_Idle);
}

SolenoidFieldMessenger::~SolenoidFieldMessenger() = default;

auto SolenoidFieldMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSolenoidMagneticField.get()) {
        Detector::Description::Solenoid::Instance().MagneticFluxDensity(fSolenoidMagneticField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Simulation::inline Field
