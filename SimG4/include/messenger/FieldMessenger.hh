#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimG4Global.hh"

class MACE::SimG4::FieldMessenger : public G4UImessenger {
public:
    static FieldMessenger* Instance();
private:
    FieldMessenger();
    ~FieldMessenger();
    FieldMessenger(const FieldMessenger&) = delete;
    FieldMessenger& operator=(const FieldMessenger&) = delete;

public:
    void Set(Field::AcceleratorField* field) { fpAcceleratorField = field; }
    void Set(Field::ParallelTransportField* field) { fpParallelTransportField = field; }
    void Set(Field::SelectorField* field) { fpSelectorField = field; }
    void Set(Field::TurnField* field) { fpTurnField = field; }
    void Set(Field::VerticalTransportField* field) { fpVerticalTransportField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Field::AcceleratorField* fpAcceleratorField;
    Field::ParallelTransportField* fpParallelTransportField;
    Field::SelectorField* fpSelectorField;
    Field::TurnField* fpTurnField;
    Field::VerticalTransportField* fpVerticalTransportField;

    G4UIdirectory* fDirectory;
    G4UIcmdWithADoubleAndUnit* fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit* fSetAcceleratorPotential;
    G4UIcmdWithADoubleAndUnit* fSetSelectorMagneticField;
};
