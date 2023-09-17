#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class SolenoidB1Field;
class SolenoidB2Field;
class SolenoidS1Field;
class SolenoidS2Field;
class SolenoidS3Field;

inline namespace Messenger {

class SolenoidFieldMessenger final : public Env::Memory::Singleton<SolenoidFieldMessenger>,
                             public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    SolenoidFieldMessenger();
    ~SolenoidFieldMessenger();

public:
    void AssignTo(gsl::not_null<SolenoidB1Field*> field) { fSolenoidB1Field = field; }
    void AssignTo(gsl::not_null<SolenoidB2Field*> field) { fSolenoidB2Field = field; }
    void AssignTo(gsl::not_null<SolenoidS1Field*> field) { fSolenoidS1Field = field; }
    void AssignTo(gsl::not_null<SolenoidS2Field*> field) { fSolenoidS2Field = field; }
    void AssignTo(gsl::not_null<SolenoidS3Field*> field) { fSolenoidS3Field = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    SolenoidB1Field* fSolenoidB1Field;
    SolenoidB2Field* fSolenoidB2Field;
    SolenoidS1Field* fSolenoidS1Field;
    SolenoidS2Field* fSolenoidS2Field;
    SolenoidS3Field* fSolenoidS3Field;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSolenoidMagneticField;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
