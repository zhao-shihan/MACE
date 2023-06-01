#include "MACE/Detector/Description/EMCalField.h++"
#include "MACE/Detector/Geometry/Fast/EMCalField.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void EMCalField::Construct(G4bool checkOverlaps) {
    const auto& description = Description::EMCalField::Instance();
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
