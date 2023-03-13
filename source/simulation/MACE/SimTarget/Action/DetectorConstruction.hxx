#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Geometry {

namespace Description {

class BeamDegrader;
class BeamMonitor;
class Target;
class World;

} // namespace Description

class EntityBase;

} // namespace Geometry

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
    using UsedDescriptions = std::tuple<Geometry::Description::BeamDegrader,
                                        Geometry::Description::BeamMonitor,
                                        Geometry::Description::Target,
                                        Geometry::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Geometry::EntityBase> fWorld;

    G4double fDensity;
    G4double fTemperature;
};

} // namespace SimTarget::Action

} // namespace MACE
