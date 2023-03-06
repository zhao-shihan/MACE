#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

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
    ~FieldMessenger();

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

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTransportMagneticField;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetLinacPotential;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetSelectorElectricField;
};

} // namespace Messenger

} // namespace MACE::SimMACE
