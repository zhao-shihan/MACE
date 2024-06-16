#include "MACE/SimEMC/Detector/EMCTunnel.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Region.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

namespace MACE::SimEMC::Detector {

using namespace Mustard::LiteralUnit;
using namespace Mustard::MathConstant;

auto EMCTunnel::Construct(G4bool checkOverlaps) -> void {
    const auto width = 50_m;
    const auto thickness = 18_m;
    const auto radius = 1_m;
    const auto length = 10_m;

    const auto nistManager = G4NistManager::Instance();
    const auto cement = nistManager->FindOrBuildMaterial("G4_CONCRETE");

    const auto box1 = Make<G4Box>(
        "tunnelMaker",
        width / 2,
        thickness,
        width / 2);

    const auto box2 = Make<G4Box>(
        "halfBox",
        26_m,
        8.5_m,
        26_m);

    const auto cylinder = Make<G4Tubs>(
        "tunnel",
        0,
        radius,
        length / 2,
        0,
        2 * pi);

    const auto tunnelMakerSolid = Make<G4SubtractionSolid>("Box - Cylinder", box1, cylinder);
    const auto solid = Make<G4SubtractionSolid>(
        "Box - halfBox",
        tunnelMakerSolid,
        box2,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, -9.6_m, 0)));
    const auto logic = Make<G4LogicalVolume>(
        solid,
        cement,
        "EMCTunnel");
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        "EMCTunnel",
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::SimEMC::Detector
