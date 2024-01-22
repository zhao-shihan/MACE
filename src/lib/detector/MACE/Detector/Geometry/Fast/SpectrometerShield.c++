#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerShield.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MathConstant;

auto SpectrometerShield::Construct(G4bool checkOverlaps) -> void {
    const auto& shield{Description::SpectrometerShield::Instance()};
    auto body{Make<G4Tubs>(
        "_temp",
        shield.InnerRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.InnerLength() / 2,
        0,
        2 * pi)};
    auto cap{Make<G4Tubs>(
        "_temp",
        shield.WindowRadius(),
        shield.InnerRadius() + shield.Thickness(),
        shield.Thickness() / 2,
        0,
        2 * pi)}; // clang-format off
    auto solid{Make<G4UnionSolid>(
            shield.Name(),
            body,
            cap, 
        G4Transform3D{{}, {0, 0, -shield.InnerLength() / 2 - shield.Thickness() / 2}})}; // clang-format on
    auto logic{Make<G4LogicalVolume>(
        solid,
        nullptr,
        shield.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        shield.Name(),
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast
