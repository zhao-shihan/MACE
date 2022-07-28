#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE {

namespace Core::Geometry {

class IEntity;

} // namespace Core::Geometry

namespace SimTarget::Action {

class DetectorConstruction final : public Utility::NonMoveableBase,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetTargetDensity(G4double val) { fDensity = val; }
    void SetTemperature(G4double val) { fTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Core::Geometry::IEntity> fBeamDegrader;
    std::shared_ptr<Core::Geometry::IEntity> fBeamMonitor;
    std::shared_ptr<Core::Geometry::IEntity> fTarget;
    std::shared_ptr<Core::Geometry::IEntity> fWorld;

    G4double fDensity;
    G4double fTemperature;
};

} // namespace SimTarget::Action

} // namespace MACE
