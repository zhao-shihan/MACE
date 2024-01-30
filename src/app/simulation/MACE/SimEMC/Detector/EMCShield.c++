#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/SimEMC/Detector/EMCShield.h++"
#include "MACE/Utility/MathConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::SimEMC::Detector {

using namespace MathConstant;

auto EMCShield::Construct(G4bool checkOverlaps) -> void {
    const auto& description = MACE::Detector::Description::EMCShield::Instance();
    const auto name = description.Name();
    const auto innerRadius = description.InnerRadius();
    const auto innerLength = description.InnerLength();
    const auto windowRadius = description.WindowRadius();
    const auto thickness = description.Thickness();

    const auto nistManager = G4NistManager::Instance();
    const auto lead = nistManager->FindOrBuildMaterial("G4_Pb");

    const auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + thickness,
        innerLength / 2,
        0,
        2 * pi);
    const auto cap = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + thickness,
        thickness / 2,
        0,
        2 * pi);
    const auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, -innerLength / 2 - thickness / 2)));
    const auto solid = Make<G4UnionSolid>(
        name,
        temp,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, innerLength / 2 + thickness / 2)));
    const auto logic = Make<G4LogicalVolume>(
        solid,
        lead,
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

} // namespace MACE::SimEMC::Detector
