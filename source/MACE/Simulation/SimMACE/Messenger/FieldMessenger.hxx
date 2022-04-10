#pragma once

#include "MACE/Simulation/SimMACE/Field/LinacField.hxx"
#include "MACE/Simulation/SimMACE/Field/FirstBendField.hxx"
#include "MACE/Simulation/SimMACE/Field/ParallelField.hxx"
#include "MACE/Simulation/SimMACE/Field/SecondBendField.hxx"
#include "MACE/Simulation/SimMACE/Field/SelectorField.hxx"
#include "MACE/Simulation/SimMACE/Field/VerticalField.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimMACE::Messenger {

using Utility::ObserverPtr;
using namespace Field;

class FieldMessenger final : public G4UImessenger {
public:
    static FieldMessenger& Instance();

private:
    FieldMessenger();
    ~FieldMessenger() noexcept = default;
    FieldMessenger(const FieldMessenger&) = delete;
    FieldMessenger& operator=(const FieldMessenger&) = delete;

public:
    void Set(ObserverPtr<FirstBendField> field) { fFirstBendField = field; }
    void Set(ObserverPtr<LinacField> field) { fLinacField = field; }
    void Set(ObserverPtr<ParallelField> field) { fParallelField = field; }
    void Set(ObserverPtr<SecondBendField> field) { fSecondBendField = field; }
    void Set(ObserverPtr<SelectorField> field) { fSelectorField = field; }
    void Set(ObserverPtr<VerticalField> field) { fVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<FirstBendField> fFirstBendField = nullptr;
    ObserverPtr<LinacField> fLinacField = nullptr;
    ObserverPtr<ParallelField> fParallelField = nullptr;
    ObserverPtr<SecondBendField> fSecondBendField = nullptr;
    ObserverPtr<SelectorField> fSelectorField = nullptr;
    ObserverPtr<VerticalField> fVerticalField = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit fSetAcceleratorPotential;
    G4UIcmdWithADoubleAndUnit fSetSelectorElectricField;
};

} // namespace MACE::Simulation::SimMACE::Messenger
