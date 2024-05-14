#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit::Density;

auto BeamMonitor::Enabled() const -> bool {
    return Description::BeamMonitor::Instance().Enabled();
}

auto BeamMonitor::Construct(G4bool checkOverlaps) -> void {
    const auto& monitor{Description::BeamMonitor::Instance()};
    const auto& accelerator{Description::Accelerator::Instance()};
    const auto& target{Description::Target::Instance()};

    G4Transform3D transform;
    switch (const auto z0{(accelerator.UpstreamLength() - accelerator.AccelerateLength()) / 2};
            target.ShapeType()) {
    case Description::Target::TargetShapeType::Cuboid: // clang-format off
        transform = {{}, {0, 0, z0 - target.Cuboid().Thickness() - monitor.DistanceToTarget() - monitor.Thickness() / 2}}; // clang-format on
        break;
    case Description::Target::TargetShapeType::MultiLayer: // clang-format off
        transform = {{}, {0, 0, z0 - target.MultiLayer().Width() / 2 - monitor.DistanceToTarget() - monitor.Thickness() / 2}}; // clang-format on
        break;
    case Description::Target::TargetShapeType::Cylinder: // clang-format off
        transform = {{}, {0, 0, z0 - target.Cylinder().Thickness() / 2 - monitor.DistanceToTarget() - monitor.Thickness() / 2}}; // clang-format on
        break;
    }

    const auto solid{Make<G4Box>(
        monitor.Name(),
        monitor.Width() / 2,
        monitor.Width() / 2,
        monitor.Thickness() / 2)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"),
        monitor.Name())};
    Make<G4PVPlacement>(
        transform,
        logic,
        monitor.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
