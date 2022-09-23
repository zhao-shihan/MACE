#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimMACE {

namespace Field {

class FirstBendField;
class LinacField;
class ParallelField;
class SecondBendField;
class SelectorField;
class VerticalField;

} // namespace Field

namespace Messenger {

using Utility::ObserverPtr;

class FieldMessenger final : public Environment::Memory::Singleton<FieldMessenger>,
                             public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    FieldMessenger();
    ~FieldMessenger() = default;

public:
    void AssignTo(ObserverPtr<Field::FirstBendField> field) { fFirstBendField = field; }
    void AssignTo(ObserverPtr<Field::LinacField> field) { fLinacField = field; }
    void AssignTo(ObserverPtr<Field::ParallelField> field) { fParallelField = field; }
    void AssignTo(ObserverPtr<Field::SecondBendField> field) { fSecondBendField = field; }
    void AssignTo(ObserverPtr<Field::SelectorField> field) { fSelectorField = field; }
    void AssignTo(ObserverPtr<Field::VerticalField> field) { fVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Field::FirstBendField> fFirstBendField;
    ObserverPtr<Field::LinacField> fLinacField;
    ObserverPtr<Field::ParallelField> fParallelField;
    ObserverPtr<Field::SecondBendField> fSecondBendField;
    ObserverPtr<Field::SelectorField> fSelectorField;
    ObserverPtr<Field::VerticalField> fVerticalField;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit fSetLinacPotential;
    G4UIcmdWithADoubleAndUnit fSetSelectorElectricField;
};

} // namespace Messenger

} // namespace MACE::SimMACE
