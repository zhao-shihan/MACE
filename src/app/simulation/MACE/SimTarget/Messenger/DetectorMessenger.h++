#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIdirectory;

namespace MACE::SimTarget {

inline namespace Action {

class DetectorConstruction;

} // namespace Action

inline namespace Messenger {

class DetectorMessenger final : public Geant4X::SingletonMessenger<DetectorMessenger,
                                                                   DetectorConstruction> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger();
    ~DetectorMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTargetDensity;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTargetTemperature;
};

} // namespace Messenger

} // namespace MACE::SimTarget
