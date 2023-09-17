#pragma once

#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector::Geometry {

class GeometryBase;

} // namespace Detector::Geometry

inline namespace Simulation {
namespace SimTarget::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void TargetDensity(G4double val) { fTargetDensity = val; }
    void TargetTemperature(G4double val) { fTargetTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::Geometry::GeometryBase> fWorld;

    G4double fTargetDensity;
    G4double fTargetTemperature;
};

} // namespace SimTarget::inline Action
} // namespace Simulation

} // namespace MACE
