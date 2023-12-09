#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Geometry/Fast/ShieldingWall.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit;
using namespace MathConstant;

auto ShieldingWall::Construct(G4bool checkOverlaps) -> void {
    const auto& description{Description::ShieldingWall::Instance()};
    const auto name{description.Name()};

    const auto height{description.Height()};
    const auto width{description.Width()};
    const auto thickness{description.Thickness()};

    const auto& solenoid{Description::Solenoid::Instance()};

    auto box = Make<G4Box>(
        name,
        width / 2,
        height / 2,
        thickness / 2);
    auto cylinder = Make<G4Tubs>(
        name,
        0,
        solenoid.OuterRadius() + 2_cm,
        thickness / 2 + 2_cm,
        0,
        2 * pi);
    auto solid = Make<G4SubtractionSolid>("Box - Cylinder", box, cylinder);
    auto logic = Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE"),
        name);
    Make<G4PVPlacement>(
        G4Transform3D{CLHEP::HepRotationY{pi / 2}, VectorCast<G4ThreeVector>(solenoid.S2Center())},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
