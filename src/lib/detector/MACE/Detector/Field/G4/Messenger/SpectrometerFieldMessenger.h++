#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class SpectrometerField;

inline namespace Messenger {

class SpectrometerFieldMessenger final : public Env::Memory::Singleton<SpectrometerFieldMessenger>,
                                     public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    SpectrometerFieldMessenger();
    ~SpectrometerFieldMessenger();

public:
    void AssignTo(gsl::not_null<SpectrometerField*> field) { fSpectrometerField = field; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    SpectrometerField* fSpectrometerField;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSpectrometerMagneticField;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
