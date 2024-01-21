#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

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

class GeometryMessenger final : public Env::Memory::Singleton<GeometryMessenger>,
                                public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    GeometryMessenger();
    ~GeometryMessenger();

public:
    auto Register(gsl::not_null<DetectorConstruction*> dc) -> void { fDetectorConstruction = dc; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    DetectorConstruction* fDetectorConstruction;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTargetDensity;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTargetTemperature;
};

} // namespace Messenger

} // namespace MACE::SimTarget
