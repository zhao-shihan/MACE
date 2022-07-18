#pragma once

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE {

namespace Core::Geometry {

class IEntity;

} // namespace Core::Geometry

namespace SimTarget::Action {

class DetectorConstruction final : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction() = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

    G4VPhysicalVolume* Construct() override;

    void SetTargetDensity(G4double val) { fDensity = val; }
    void SetTemperature(G4double val) { fTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlaps = checkOverlaps; }

private:
    std::shared_ptr<Core::Geometry::IEntity> fBeamDegrader;
    std::shared_ptr<Core::Geometry::IEntity> fBeamMonitor;
    std::shared_ptr<Core::Geometry::IEntity> fTarget;
    std::shared_ptr<Core::Geometry::IEntity> fWorld;

    G4double fDensity;
    G4double fTemperature;

    G4bool fCheckOverlaps = false;
};

} // namespace SimTarget::Action

} // namespace MACE
