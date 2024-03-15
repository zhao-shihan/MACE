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

namespace Detector::Definition {

class DefinitionBase;

} // namespace Detector::Definition

namespace SimTarget::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Detector::Definition::DefinitionBase> fWorld;
};

} // namespace SimTarget::inline Action

} // namespace MACE
