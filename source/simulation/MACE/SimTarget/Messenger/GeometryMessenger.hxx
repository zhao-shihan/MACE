#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UImessenger.hh"

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

using Utility::ObserverPtr;

class GeometryMessenger final : public Environment::Memory::Singleton<GeometryMessenger>,
                                public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    GeometryMessenger();
    ~GeometryMessenger();
    GeometryMessenger(const GeometryMessenger&) = delete;
    GeometryMessenger& operator=(const GeometryMessenger&) = delete;

public:
    void SetTo(ObserverPtr<Action::DetectorConstruction> dc) { fDetectorConstruction = dc; }

    void SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) override;

private:
    ObserverPtr<Action::DetectorConstruction> fDetectorConstruction;

    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithAString> fIxportDescription;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTargetDensity;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTemperature;
};

} // namespace Messenger

} // namespace MACE::SimTarget
