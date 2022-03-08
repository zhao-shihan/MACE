#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

#include "SimMACE/Messenger/FieldMessenger.hxx"
#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Field/ParallelField.hxx"
#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Field/VerticalField.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::Messenger;

FieldMessenger& FieldMessenger::Instance() {
    static FieldMessenger instance;
    return instance;
}

FieldMessenger::FieldMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Field/"),
    fSetTransportMagneticField("/MACE/Field/SetTransportMagneticField", this),
    fSetAcceleratorPotential("/MACE/Field/SetAcceleratorPotential", this),
    fSetSelectorElectricField("/MACE/Field/SetSelectorElectricField", this) {

    fDirectory.SetGuidance("Detector field controller.");

    fSetTransportMagneticField.SetGuidance("Set transport magnetic field.");
    fSetTransportMagneticField.SetParameterName("B", false);
    fSetTransportMagneticField.SetUnitCategory("Magnetic flux density");
    fSetTransportMagneticField.AvailableForStates(G4State_Idle);

    fSetAcceleratorPotential.SetGuidance("Set accelerator electric potential. (Selector electric field changes, respectively.)");
    fSetAcceleratorPotential.SetParameterName("V", false);
    fSetAcceleratorPotential.SetUnitCategory("Electric potential");
    fSetAcceleratorPotential.AvailableForStates(G4State_Idle);

    fSetSelectorElectricField.SetGuidance("Set selector electric field. (Selector magnetic field changes, respectively, to ensure the seleted kinetic energy stays the same.)");
    fSetSelectorElectricField.SetParameterName("E", false);
    fSetSelectorElectricField.SetUnitCategory("Electric field");
    fSetSelectorElectricField.AvailableForStates(G4State_Idle);
}

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetTransportMagneticField)) {
        const auto B = fSetTransportMagneticField.GetNewDoubleValue(value);
        fAcceleratorField->SetTransportBField(B);
        fFirstBendField->SetTransportMagneticField(B);
        fParallelField->SetFieldNorm(B);
        fSecondBendField->SetTransportMagneticField(B);
        fSelectorField->SetTransportField(B);
        fVerticalField->SetFieldNorm(B);
    } else if (command == std::addressof(fSetAcceleratorPotential)) {
        const auto V = fSetAcceleratorPotential.GetNewDoubleValue(value);
        fAcceleratorField->SetAcceleratorPotential(V);
        fSelectorField->SetSelectEnergy(eplus * std::abs(V));
    } else if (command == std::addressof(fSetSelectorElectricField)) {
        fSelectorField->SetSelectorElectricField(fSetSelectorElectricField.GetNewDoubleValue(value));
    }
}
