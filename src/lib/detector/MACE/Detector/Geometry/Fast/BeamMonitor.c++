#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::Density;

bool BeamMonitor::Enabled() const {
    return Description::BeamMonitor::Instance().Enabled();
}

auto BeamMonitor::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::BeamMonitor::Instance();
    const auto name = description.Name();
    const auto width = description.Width();
    const auto thickness = description.Thickness();
    const auto transform = description.CalcTransform();

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        thickness / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
