#pragma once

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimTarget::Messenger {

class GeometryMessenger final : public G4UImessenger {
public:
    static GeometryMessenger& Instance();

private:
    GeometryMessenger();
    ~GeometryMessenger() noexcept = default;
    GeometryMessenger(const GeometryMessenger&) = delete;
    GeometryMessenger& operator=(const GeometryMessenger&) = delete;

public:
    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    G4UIdirectory fDirectory;
    G4UIcmdWith3VectorAndUnit fSetWorldHalfExtent;
    G4UIcmdWithADoubleAndUnit fSetTargetWidth;
    G4UIcmdWithADoubleAndUnit fSetTargetThickness;
    G4UIcmdWithADoubleAndUnit fSetTargetDensity;
    G4UIcmdWithADoubleAndUnit fSetTemperature;
    G4UIcmdWithAString fSetFineStructure;
};

} // namespace MACE::Simulation::SimTarget::Messenger
