#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Geometry/Fast/AcceleratorField.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void AcceleratorField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::AcceleratorField::Instance();
    const auto name = description.Name();
    const auto radius = description.Radius();
    const auto length = description.Length();
    const auto transform = description.CalcTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        twopi);
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
