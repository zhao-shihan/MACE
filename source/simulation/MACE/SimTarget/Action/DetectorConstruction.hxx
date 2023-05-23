#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector {

namespace Description {

class BeamDegrader;
class BeamMonitor;
class Target;
class World;

} // namespace Description

namespace Geometry {

class GeometryBase;

} // namespace Geometry

} // namespace Detector

namespace SimTarget::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetTargetDensity(G4double val) { fDensity = val; }
    void SetTemperature(G4double val) { fTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::Geometry::GeometryBase> fWorld;

    G4double fDensity;
    G4double fTemperature;
};

} // namespace SimTarget::inline Action

} // namespace MACE
