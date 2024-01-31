#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Detector/Geometry/ShieldingWall.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationY.h"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry {

using namespace LiteralUnit;
using namespace MathConstant;

auto ShieldingWall::Construct(G4bool checkOverlaps) -> void {
    const auto& shieldingWall{Description::ShieldingWall::Instance()};
    const auto name{shieldingWall.Name()};
    const auto& world{Description::World::Instance()};
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& spectrometerShield{Description::SpectrometerShield::Instance()};
    const auto& emcField{Description::EMCField::Instance()};
    const auto& emcShield{Description::EMCShield::Instance()};

    auto box = Make<G4Box>(
        name,
        shieldingWall.Thickness() / 2,
        world.HalfYExtent(),
        world.HalfZExtent());
    auto cylinder = Make<G4Tubs>(
        name,
        0,
        solenoid.FieldRadius() + 2_cm,
        solenoid.S2Length() / 2 + 2_cm,
        0,
        2 * pi); // clang-format off
    const G4Transform3D wallTransform{
        {},
        {Math::MidPoint(spectrometerShield.InnerRadius() + spectrometerShield.Thickness(),
                        emcField.Center()[0] - emcShield.InnerRadius() - emcShield.Thickness()), 0, 0}}; // clang-format on
    auto solid = Make<G4SubtractionSolid>(
        "_temp",
        box,
        cylinder,
        wallTransform.inverse() * G4Transform3D{CLHEP::HepRotationY{pi / 2}, VectorCast<G4ThreeVector>(solenoid.S2Center())});
    auto logic = Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE"),
        name);
    Make<G4PVPlacement>(
        wallTransform,
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry
