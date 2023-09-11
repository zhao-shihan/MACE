#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class EMCField;

inline namespace Messenger {

class EMCFieldMessenger final : public Env::Memory::Singleton<EMCFieldMessenger>,
                                  public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    EMCFieldMessenger();
    ~EMCFieldMessenger();

public:
    void AssignTo(gsl::not_null<EMCField*> field) { fEMCField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    EMCField* fEMCField;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSpectrometerMagneticField;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
