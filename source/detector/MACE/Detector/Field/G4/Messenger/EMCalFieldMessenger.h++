#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class EMCalField;

inline namespace Messenger {

class EMCalFieldMessenger final : public Env::Memory::Singleton<EMCalFieldMessenger>,
                                  public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    EMCalFieldMessenger();
    ~EMCalFieldMessenger();

public:
    void AssignTo(gsl::not_null<EMCalField*> field) { fEMCalField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    EMCalField* fEMCalField;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSpectrometerMagneticField;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
