#pragma once

#include "MACE/Core/Geometry/Entity/Fast/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Entity/Fast/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Core/Geometry/Entity/Fast/World.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Material.hh"
#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE::SimTarget::Action {

using namespace MACE::Core::Geometry::Entity::Fast;
using MACE::Utility::ObserverPtr;

class DetectorConstruction final : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction() noexcept = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

    G4VPhysicalVolume* Construct() override;

    void SetTargetDensity(G4double val) { fDensity = val; }
    void SetTemperature(G4double val) { fTemperature = val; }

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlaps = checkOverlaps; }

private:
    std::shared_ptr<BeamDegrader> fBeamDegrader;
    std::shared_ptr<BeamMonitor> fBeamMonitor;
    std::shared_ptr<Target> fTarget;
    std::shared_ptr<World> fWorld;

    G4double fDensity;
    G4double fTemperature;

    G4bool fCheckOverlaps = false;
};

} // namespace MACE::SimTarget::Action
