#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerField.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto SpectrometerField::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::SpectrometerField::Instance();
    auto name = description.Name();
    auto length = description.Length();
    auto radius = description.Radius();

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
        G4Transform3D(),
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
