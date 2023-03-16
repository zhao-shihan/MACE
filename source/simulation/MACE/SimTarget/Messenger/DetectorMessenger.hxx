#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UICommand;
class G4UIdirectory;

namespace MACE::SimTarget {

namespace Action {

class DetectorConstruction;

} // namespace Action

namespace Messenger {

class GeometryMessenger final : public Env::Memory::Singleton<GeometryMessenger>,
                                public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    GeometryMessenger();
    ~GeometryMessenger();

public:
    void AssignTo(gsl::not_null<Action::DetectorConstruction*> dc) { fDetectorConstruction = dc; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::DetectorConstruction* fDetectorConstruction;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTargetDensity;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTemperature;
};

} // namespace Messenger

} // namespace MACE::SimTarget
