#include "MACE/SimMACE/Field/FirstBendField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Field/SecondBendField.hxx"
#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimMACE::Messenger {

FieldMessenger::FieldMessenger() :
    Singleton(),
    G4UImessenger(),
    fFirstBendField(nullptr),
    fLinacField(nullptr),
    fParallelField(nullptr),
    fSecondBendField(nullptr),
    fSelectorField(nullptr),
    fVerticalField(nullptr),
    fDirectory(),
    fSetTransportMagneticField(),
    fSetLinacPotential(),
    fSetSelectorElectricField() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fSetTransportMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SetTransportMagneticField", this);
    fSetTransportMagneticField->SetGuidance("Set transport magnetic field.");
    fSetTransportMagneticField->SetParameterName("B", false);
    fSetTransportMagneticField->SetUnitCategory("Magnetic flux density");
    fSetTransportMagneticField->AvailableForStates(G4State_Idle);

    fSetLinacPotential = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SetLinacPotential", this);
    fSetLinacPotential->SetGuidance("Set linac electric potential. "
                                    "(Selector electric field changes, respectively.)");
    fSetLinacPotential->SetParameterName("V", false);
    fSetLinacPotential->SetUnitCategory("Electric potential");
    fSetLinacPotential->AvailableForStates(G4State_Idle);

    fSetSelectorElectricField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SetSelectorElectricField", this);
    fSetSelectorElectricField->SetGuidance("Set selector electric field. (Selector magnetic field changes, respectively, "
                                           "to ensure the seleted kinetic energy stays the same.)");
    fSetSelectorElectricField->SetParameterName("E", false);
    fSetSelectorElectricField->SetUnitCategory("Electric field");
    fSetSelectorElectricField->AvailableForStates(G4State_Idle);
}

FieldMessenger::~FieldMessenger() = default;

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetTransportMagneticField.get()) {
        const auto B = fSetTransportMagneticField->GetNewDoubleValue(value);
        fLinacField->SetTransportBField(B);
        fFirstBendField->SetTransportMagneticField(B);
        fParallelField->SetFieldNorm(B);
        fSecondBendField->SetTransportMagneticField(B);
        fSelectorField->SetTransportField(B);
        fVerticalField->SetFieldNorm(B);
    } else if (command == fSetLinacPotential.get()) {
        const auto V = fSetLinacPotential->GetNewDoubleValue(value);
        fLinacField->SetLinacPotential(V);
        fSelectorField->SetSelectEnergy(std::abs(V));
    } else if (command == fSetSelectorElectricField.get()) {
        fSelectorField->SetSelectorElectricField(fSetSelectorElectricField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::SimMACE::Messenger
