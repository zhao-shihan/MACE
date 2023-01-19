#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

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

class FieldMessenger final : public Env::Memory::Singleton<FieldMessenger>,
                             public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    FieldMessenger();
    ~FieldMessenger() = default;

public:
    void AssignTo(gsl::not_null<Field::FirstBendField*> field) { fFirstBendField = field; }
    void AssignTo(gsl::not_null<Field::LinacField*> field) { fLinacField = field; }
    void AssignTo(gsl::not_null<Field::ParallelField*> field) { fParallelField = field; }
    void AssignTo(gsl::not_null<Field::SecondBendField*> field) { fSecondBendField = field; }
    void AssignTo(gsl::not_null<Field::SelectorField*> field) { fSelectorField = field; }
    void AssignTo(gsl::not_null<Field::VerticalField*> field) { fVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Field::FirstBendField* fFirstBendField;
    Field::LinacField* fLinacField;
    Field::ParallelField* fParallelField;
    Field::SecondBendField* fSecondBendField;
    Field::SelectorField* fSelectorField;
    Field::VerticalField* fVerticalField;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetTransportMagneticField;
    G4UIcmdWithADoubleAndUnit fSetLinacPotential;
    G4UIcmdWithADoubleAndUnit fSetSelectorElectricField;
};

} // namespace Messenger

} // namespace MACE::SimMACE
