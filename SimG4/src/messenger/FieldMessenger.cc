#include "G4UIdirectory.hh"

#include "messenger/FieldMessenger.hh"
#include "detector/field/AcceleratorField.hh"
#include "detector/field/ParallelTransportField.hh"
#include "detector/field/SelectorField.hh"
#include "detector/field/TurnField.hh"
#include "detector/field/VerticalTransportField.hh"
#include "Analysis.hh"

using namespace MACE::SimG4;

FieldMessenger* FieldMessenger::Instance() {
    static FieldMessenger instance;
    return &instance;
}

FieldMessenger::FieldMessenger() :
    G4UImessenger() {

    fDirectory = new G4UIdirectory("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSetTransportMagneticField = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetTransportMagneticField", this);
    fSetTransportMagneticField->SetGuidance("Set transport magnetic field.");
    fSetTransportMagneticField->SetParameterName("B", false);
    fSetTransportMagneticField->SetUnitCategory("Magnetic flux density");
    fSetTransportMagneticField->AvailableForStates(G4State_PreInit, G4State_Idle);

    fSetAcceleratorPotential = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetAcceleratorPotential", this);
    fSetAcceleratorPotential->SetGuidance("Set accelerator electric potential."
        "(Selector field changes, respectively.)");
    fSetAcceleratorPotential->SetParameterName("V", false);
    fSetAcceleratorPotential->SetUnitCategory("Electric potential");
    fSetAcceleratorPotential->AvailableForStates(G4State_PreInit, G4State_Idle);

    fSetSelectorMagneticField = new G4UIcmdWithADoubleAndUnit("/MACE/Field/SetSelectorMagneticField", this);
    fSetSelectorMagneticField->SetGuidance("Set selector magnetic field. "
        "(Selector electric field changes, respectively, to ensure the seleted kinetic energy stays the same.)");
    fSetSelectorMagneticField->SetParameterName("B", false);
    fSetSelectorMagneticField->SetUnitCategory("Magnetic flux density");
    fSetSelectorMagneticField->AvailableForStates(G4State_PreInit, G4State_Idle);
}

FieldMessenger::~FieldMessenger() {}

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetTransportMagneticField) {
        const auto B = fSetTransportMagneticField->GetNewDoubleValue(value);
        fpAcceleratorField->SetTransportBField(B);
        fpParallelTransportField->SetFieldNorm(B);
        fpSelectorField->SetTransportField(B);
        fpTurnField->SetTransportMagneticField(B);
        fpVerticalTransportField->SetFieldNorm(B);
    } else if (command == fSetAcceleratorPotential) {
        const auto V = fSetAcceleratorPotential->GetNewDoubleValue(value);
        fpAcceleratorField->SetAcceleratorPotential(V);
        fpSelectorField->SetSelectEnergy(eplus * V);
        fpAnalysis->SetEkinOfOrbital(eplus * V);
    } else if (command == fSetSelectorMagneticField) {
        fpSelectorField->SetSelectorMagneticField(fSetSelectorMagneticField->GetNewDoubleValue(value));
    }
}
