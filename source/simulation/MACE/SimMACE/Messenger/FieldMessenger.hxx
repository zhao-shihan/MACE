#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::SimMACE {

inline namespace Field {

class FirstBendField;
class LinacField;
class ParallelField;
class SecondBendField;
class SelectorField;
class VerticalField;

} // inline namespace Field

inline namespace Messenger {

class FieldMessenger final : public Env::Memory::Singleton<FieldMessenger>,
                             public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    FieldMessenger();
    ~FieldMessenger();

public:
    void AssignTo(gsl::not_null<FirstBendField*> field) { fFirstBendField = field; }
    void AssignTo(gsl::not_null<LinacField*> field) { fLinacField = field; }
    void AssignTo(gsl::not_null<ParallelField*> field) { fParallelField = field; }
    void AssignTo(gsl::not_null<SecondBendField*> field) { fSecondBendField = field; }
    void AssignTo(gsl::not_null<SelectorField*> field) { fSelectorField = field; }
    void AssignTo(gsl::not_null<VerticalField*> field) { fVerticalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    FirstBendField* fFirstBendField;
    LinacField* fLinacField;
    ParallelField* fParallelField;
    SecondBendField* fSecondBendField;
    SelectorField* fSelectorField;
    VerticalField* fVerticalField;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTransportMagneticField;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fLinacPotential;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSelectorElectricField;
};

} // inline namespace Messenger

} // namespace MACE::SimMACE
