#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

namespace MACE::Detector::Field::G4 {

class EMCField;

inline namespace Messenger {

class EMCFieldMessenger final : public Geant4X::SingletonMessenger<EMCFieldMessenger> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMCFieldMessenger();
    ~EMCFieldMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSpectrometerMagneticField;
};

} // namespace Messenger

} // namespace MACE::Detector::Field::G4
