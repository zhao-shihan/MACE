#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"

namespace MACE::Simulation::SimTarget {

class DetectorConstruction final : public G4VUserDetectorConstruction {
public:
    DetectorConstruction() = default;
    ~DetectorConstruction() noexcept = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlaps = checkOverlaps; }

private:
    G4bool fCheckOverlaps = false;
};

} // namespace MACE::Simulation::SimTarget
