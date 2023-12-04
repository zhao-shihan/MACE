#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Geometry/Fast/EMCField.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto EMCField::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::EMCField::Instance();
    auto name = description.Name();
    auto radius = description.Radius();
    auto length = description.Length();
    auto transform = description.CalcTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        2 * pi);
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
