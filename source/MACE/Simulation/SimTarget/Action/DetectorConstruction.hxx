#pragma once

#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Core/Geometry/Entity/Fast/World.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE::Simulation::SimTarget::Action {

using namespace MACE::Core::Geometry::Entity::Fast;

class DetectorConstruction final : public G4VUserDetectorConstruction {
public:
    DetectorConstruction() = default;
    ~DetectorConstruction() noexcept = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlaps = checkOverlaps; }

private:
    std::shared_ptr<Target> fTarget;
    std::shared_ptr<World> fWorld;

    G4bool fCheckOverlaps = false;
};

} // namespace MACE::Simulation::SimTarget
