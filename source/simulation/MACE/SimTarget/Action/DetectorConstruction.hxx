#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Core::Geometry {

namespace Description {

class BeamDegrader;
class BeamMonitor;
class Target;
class World;

} // namespace Description

class IEntity;

} // namespace Core::Geometry

namespace SimTarget::Action {

class DetectorConstruction final : public Env::Memory::FreeSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetTargetDensity(G4double val) { fDensity = val; }
    void SetTemperature(G4double val) { fTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using UsedDescriptions = std::tuple<Core::Geometry::Description::BeamDegrader,
                                        Core::Geometry::Description::BeamMonitor,
                                        Core::Geometry::Description::Target,
                                        Core::Geometry::Description::World>;

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
