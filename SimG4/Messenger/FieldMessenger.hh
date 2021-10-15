#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimG4/Global.hh"

class MACE::SimG4::Messenger::FieldMessenger final : public G4UImessenger {
public:
    static FieldMessenger* Instance();
private:
    FieldMessenger();
    ~FieldMessenger();
    FieldMessenger(const FieldMessenger&) = delete;
    FieldMessenger& operator=(const FieldMessenger&) = delete;

public:
    void Set(Field::AcceleratorField* field) { fpAcceleratorField = field; }
    void Set(Field::FirstBendField* field) { fpFirstBendField = field; }
    void Set(Field::ParallelField* field) { fpParallelField = field; }
    void Set(Field::SecondBendField* field) { fpSecondBendField = field; }
    void Set(Field::SelectorField* field) { fpSelectorField = field; }
    void Set(Field::VerticalField* field) { fpVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Field::AcceleratorField* fpAcceleratorField = nullptr;
    Field::FirstBendField* fpFirstBendField = nullptr;
    Field::ParallelField* fpParallelField = nullptr;
    Field::SecondBendField* fpSecondBendField = nullptr;
    Field::SelectorField* fpSelectorField = nullptr;
    Field::VerticalField* fpVerticalField = nullptr;

    G4UIdirectory* fDirectory;
    G4UIcmdWithADoubleAndUnit* fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit* fSetAcceleratorPotential;
    G4UIcmdWithADoubleAndUnit* fSetSelectorMagneticField;
};
