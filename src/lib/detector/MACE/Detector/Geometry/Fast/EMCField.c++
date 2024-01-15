#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Geometry/Fast/EMCField.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto EMCField::Construct(G4bool checkOverlaps) -> void {
    const auto& emcField{Description::EMCField::Instance()};
    auto name{emcField.Name()};

    auto solid = Make<G4Tubs>(
        name,
        0,
        emcField.Radius(),
        emcField.Length() / 2,
        0,
        2 * pi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D{{}, VectorCast<G4ThreeVector>(emcField.Center())},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
