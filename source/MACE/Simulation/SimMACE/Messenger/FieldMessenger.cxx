#include "MACE/Simulation/SimMACE/Messenger/FieldMessenger.hxx"

#include "G4UIdirectory.hh"

using MACE::Simulation::SimMACE::Messenger::FieldMessenger;

FieldMessenger& FieldMessenger::Instance() {
    static FieldMessenger instance;
    return instance;
}

FieldMessenger::FieldMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Field/"),
    fSetTransportMagneticField("/MACE/Field/SetTransportMagneticField", this),
    fSetLinacPotential("/MACE/Field/SetLinacPotential", this),
    fSetSelectorElectricField("/MACE/Field/SetSelectorElectricField", this) {

    fDirectory.SetGuidance("Detector field controller.");

    fSetTransportMagneticField.SetGuidance("Set transport magnetic field.");
    fSetTransportMagneticField.SetParameterName("B", false);
    fSetTransportMagneticField.SetUnitCategory("Magnetic flux density");
    fSetTransportMagneticField.AvailableForStates(G4State_Idle);

    fSetLinacPotential.SetGuidance(
        "Set linac electric potential. (Selector electric field changes, respectively.)");
    fSetLinacPotential.SetParameterName("V", false);
    fSetLinacPotential.SetUnitCategory("Electric potential");
    fSetLinacPotential.AvailableForStates(G4State_Idle);

    fSetSelectorElectricField.SetGuidance(
        "Set selector electric field. (Selector magnetic field changes, respectively, to ensure the seleted kinetic energy stays the same.)");
    fSetSelectorElectricField.SetParameterName("E", false);
    fSetSelectorElectricField.SetUnitCategory("Electric field");
    fSetSelectorElectricField.AvailableForStates(G4State_Idle);
}

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetTransportMagneticField)) {
        const auto B = fSetTransportMagneticField.GetNewDoubleValue(value);
        fLinacField->SetTransportBField(B);
        fFirstBendField->SetTransportMagneticField(B);
        fParallelField->SetFieldNorm(B);
        fSecondBendField->SetTransportMagneticField(B);
        fSelectorField->SetTransportField(B);
        fVerticalField->SetFieldNorm(B);
    } else if (command == std::addressof(fSetLinacPotential)) {
        const auto V = fSetLinacPotential.GetNewDoubleValue(value);
        fLinacField->SetLinacPotential(V);
        fSelectorField->SetSelectEnergy(std::abs(V));
    } else if (command == std::addressof(fSetSelectorElectricField)) {
        fSelectorField->SetSelectorElectricField(fSetSelectorElectricField.GetNewDoubleValue(value));
    }
}
