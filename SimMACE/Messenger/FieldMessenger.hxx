#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Messenger::FieldMessenger final :
    public G4UImessenger {
public:
    static FieldMessenger& Instance();

private:
    FieldMessenger();
    ~FieldMessenger() noexcept = default;
    FieldMessenger(const FieldMessenger&) = delete;
    FieldMessenger& operator=(const FieldMessenger&) = delete;

public:
    void Set(ObserverPtr<Field::AcceleratorField> field) { fAcceleratorField = field; }
    void Set(ObserverPtr<Field::FirstBendField> field) { fFirstBendField = field; }
    void Set(ObserverPtr<Field::ParallelField> field) { fParallelField = field; }
    void Set(ObserverPtr<Field::SecondBendField> field) { fSecondBendField = field; }
    void Set(ObserverPtr<Field::SelectorField> field) { fSelectorField = field; }
    void Set(ObserverPtr<Field::VerticalField> field) { fVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Field::AcceleratorField> fAcceleratorField = nullptr;
    ObserverPtr<Field::FirstBendField> fFirstBendField = nullptr;
    ObserverPtr<Field::ParallelField> fParallelField = nullptr;
    ObserverPtr<Field::SecondBendField> fSecondBendField = nullptr;
    ObserverPtr<Field::SelectorField> fSelectorField = nullptr;
    ObserverPtr<Field::VerticalField> fVerticalField = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit fSetAcceleratorPotential;
    G4UIcmdWithADoubleAndUnit fSetSelectorMagneticField;
};
