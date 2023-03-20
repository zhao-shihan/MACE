#include "MACE/SimMACE/Field/FirstBendField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Field/SecondBendField.hxx"
#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimMACE::inline Messenger {

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
    fTransportMagneticField(),
    fLinacPotential(),
    fSelectorElectricField() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Field/");
    fDirectory->SetGuidance("Detector field controller.");

    fTransportMagneticField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/TransportMagneticField", this);
    fTransportMagneticField->SetGuidance("Set transport magnetic field.");
    fTransportMagneticField->SetParameterName("B", false);
    fTransportMagneticField->SetUnitCategory("Magnetic flux density");
    fTransportMagneticField->AvailableForStates(G4State_Idle);

    fLinacPotential = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/LinacPotential", this);
    fLinacPotential->SetGuidance("Set linac electric potential. "
                                 "(Selector electric field changes, respectively.)");
    fLinacPotential->SetParameterName("V", false);
    fLinacPotential->SetUnitCategory("Electric potential");
    fLinacPotential->AvailableForStates(G4State_Idle);

    fSelectorElectricField = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Field/SelectorElectricField", this);
    fSelectorElectricField->SetGuidance("Set selector electric field. (Selector magnetic field changes, respectively, "
                                        "to ensure the seleted kinetic energy stays the same.)");
    fSelectorElectricField->SetParameterName("E", false);
    fSelectorElectricField->SetUnitCategory("Electric field");
    fSelectorElectricField->AvailableForStates(G4State_Idle);
}

FieldMessenger::~FieldMessenger() = default;

void FieldMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fTransportMagneticField.get()) {
        const auto B = fTransportMagneticField->GetNewDoubleValue(value);
        fLinacField->SetTransportBField(B);
        fFirstBendField->SetTransportMagneticField(B);
        fParallelField->SetFieldNorm(B);
        fSecondBendField->SetTransportMagneticField(B);
        fSelectorField->SetTransportField(B);
        fVerticalField->SetFieldNorm(B);
    } else if (command == fLinacPotential.get()) {
        const auto V = fLinacPotential->GetNewDoubleValue(value);
        fLinacField->SetLinacPotential(V);
        fSelectorField->SetSelectEnergy(std::abs(V));
    } else if (command == fSelectorElectricField.get()) {
        fSelectorField->SetSelectorElectricField(fSelectorElectricField->GetNewDoubleValue(value));
    }
}

} // namespace MACE::SimMACE::inline Messenger
