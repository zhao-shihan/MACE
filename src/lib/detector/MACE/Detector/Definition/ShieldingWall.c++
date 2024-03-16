#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Description/World.h++"
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

namespace MACE::Detector::Definition {

using namespace LiteralUnit;
using namespace MathConstant;

auto ShieldingWall::Construct(G4bool checkOverlaps) -> void {
    const auto& shieldingWall{Description::ShieldingWall::Instance()};
    const auto& world{Description::World::Instance()};
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& spectrometerShield{Description::SpectrometerShield::Instance()};
    const auto& emcField{Description::EMCField::Instance()};
    const auto& emcShield{Description::EMCShield::Instance()};

    const auto x1{Math::MidPoint(spectrometerShield.InnerRadius() + spectrometerShield.Thickness(),
                                 emcField.Center()[0] - emcShield.InnerRadius() - emcShield.Thickness())};
    const auto concrete{G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE")};
    { // wall 1
        const auto box{Make<G4Box>(
            shieldingWall.Name(),
            shieldingWall.Thickness() / 2,
            world.HalfYExtent(),
            world.HalfZExtent() / 2)};
        const auto cylinder{Make<G4Tubs>(
            shieldingWall.Name(),
            0,
            solenoid.FieldRadius() + 2_cm,
            solenoid.S2Length() / 2 + 2_cm,
            0,
            2 * pi)}; // clang-format off
    const G4Transform3D wallTransform{{}, {x1, 0, world.HalfZExtent() / 2}}; // clang-format on
        const auto solid{Make<G4SubtractionSolid>(
            "_temp",
            box,
            cylinder,
            wallTransform.inverse() * G4Transform3D{CLHEP::HepRotationY{pi / 2}, VectorCast<G4ThreeVector>(solenoid.S2Center())})};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            concrete,
            shieldingWall.Name())};
        Make<G4PVPlacement>(
            wallTransform,
            logic,
            shieldingWall.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    { // wall 2
        const auto solid{Make<G4Box>(
            shieldingWall.Name(),
            world.HalfXExtent() - x1 - shieldingWall.Thickness() / 2,
            world.HalfYExtent(),
            shieldingWall.Thickness() / 2)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            concrete,
            shieldingWall.Name())};
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {world.HalfXExtent(), 0, solid->GetZHalfLength()}}, // clang-format on
            logic,
            shieldingWall.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
