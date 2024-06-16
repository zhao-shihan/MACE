#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/World.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationY.h"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

#include "muc/numeric"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto ShieldingWall::Enabled() const -> bool {
    return Description::ShieldingWall::Instance().Enabled();
}

auto ShieldingWall::Construct(G4bool checkOverlaps) -> void {
    const auto& wall{Description::ShieldingWall::Instance()};
    const auto& world{Description::World::Instance()};
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& mmsShield{Description::MMSShield::Instance()};
    const auto& emcField{Description::EMCField::Instance()};
    const auto& emcShield{Description::EMCShield::Instance()};

    const G4ThreeVector mmsShieldCorner{mmsShield.InnerRadius() + mmsShield.Thickness(), 0, mmsShield.InnerLength() / 2 + mmsShield.Thickness()}; // clang-format off
    const auto emcShieldCorner{Mustard::VectorCast<G4ThreeVector>(emcField.Center()) + 
                               G4ThreeVector{-emcShield.InnerRadius() - emcShield.Thickness(), 0 , -emcShield.InnerLength() / 2 - emcShield.Thickness()}}; // clang-format on
    const auto wall1Displacement{muc::midpoint(mmsShieldCorner, emcShieldCorner)};

    const auto concrete{G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE")};

    { // wall 1
        const auto box{Make<G4Box>(
            wall.Name(),
            wall.Thickness() / 2,
            world.HalfYExtent(),
            wall.Length() / 2)};
        const auto cylinder{Make<G4Tubs>(
            wall.Name(),
            0,
            solenoid.FieldRadius() + 3_cm,
            world.HalfXExtent(),
            0,
            2_pi)}; // clang-format off
    const G4Transform3D wallTransform{CLHEP::HepRotationY{-wall.Rotation()}, wall1Displacement}; // clang-format on
        const auto solid{Make<G4SubtractionSolid>(
            "_temp",
            box,
            cylinder,
            wallTransform.inverse() * G4Transform3D{CLHEP::HepRotationY{0.5_pi}, Mustard::VectorCast<G4ThreeVector>(solenoid.S2Center())})};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            concrete,
            wall.Name())};
        Make<G4PVPlacement>(
            wallTransform,
            logic,
            wall.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    /* { // wall 2
        const auto solid{Make<G4Box>(
            wall.Name(),
            world.HalfXExtent() - x1 - wall.Thickness() / 2,
            world.HalfYExtent(),
            wall.Thickness() / 2)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            concrete,
            wall.Name())};
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {world.HalfXExtent(), 0, solid->GetZHalfLength()}}, // clang-format on
            logic,
            wall.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    } */
}

} // namespace MACE::Detector::Definition
