#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto SolenoidB1::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::Solenoid::Instance();
    const auto name = "SolenoidB1";
    const auto innerRadius = description.InnerRadius();
    const auto outerRadius = description.OuterRadius();
    const auto bendRadius = description.B1Radius();

    auto solid = Make<G4Torus>(
        name,
        innerRadius,
        outerRadius,
        bendRadius,
        pi / 2,
        pi / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
