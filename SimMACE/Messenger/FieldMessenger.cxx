#include "G4UIdirectory.hh"

#include "SimMACE/Messenger/FieldMessenger.hxx"
#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Field/ParallelField.hxx"
#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Field/VerticalField.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE::Messenger;

FieldMessenger& FieldMessenger::Instance() {
    static FieldMessenger instance;
    return instance;
}

FieldMessenger::FieldMessenger() :
    G4UImessenger() {

    fDirectory = new G4UIdirectory("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSetTransportMagneticField = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetTransportMagneticField", this);
    fSetTransportMagneticField->SetGuidance("Set transport magnetic field.");
    fSetTransportMagneticField->SetParameterName("B", false);
    fSetTransportMagneticField->SetUnitCategory("Magnetic flux density");
    fSetTransportMagneticField->AvailableForStates(G4State_Idle);

    fSetAcceleratorPotential = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetAcceleratorPotential", this);
    fSetAcceleratorPotential->SetGuidance("Set accelerator electric potential."
        "(Selector electric field changes, respectively.)");
    fSetAcceleratorPotential->SetParameterName("V", false);
    fSetAcceleratorPotential->SetUnitCategory("Electric potential");
    fSetAcceleratorPotential->AvailableForStates(G4State_Idle);

    fSetSelectorMagneticField = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetSelectorMagneticField", this);
    fSetSelectorMagneticField->SetGuidance("Set selector magnetic field. "
        "(Selector electric field changes, respectively, to ensure the seleted kinetic energy stays the same.)");
    fSetSelectorMagneticField->SetParameterName("B", false);
    fSetSelectorMagneticField->SetUnitCategory("Magnetic flux density");
    fSetSelectorMagneticField->AvailableForStates(G4State_Idle);
}

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetTransportMagneticField) {
        const auto B = fSetTransportMagneticField->GetNewDoubleValue(value);
        fpAcceleratorField->SetTransportBField(B);
        fpFirstBendField->SetTransportMagneticField(B);
        fpParallelField->SetFieldNorm(B);
        fpSecondBendField->SetTransportMagneticField(B);
        fpSelectorField->SetTransportField(B);
        fpVerticalField->SetFieldNorm(B);
    } else if (command == fSetAcceleratorPotential) {
        const auto V = fSetAcceleratorPotential->GetNewDoubleValue(value);
        fpAcceleratorField->SetAcceleratorPotential(V);
        fpSelectorField->SetSelectEnergy(eplus * V);
    } else if (command == fSetSelectorMagneticField) {
        fpSelectorField->SetSelectorMagneticField(fSetSelectorMagneticField->GetNewDoubleValue(value));
    }
}
