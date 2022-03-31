#include "Core/Geometry/Description/SpectrometerBody.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerBody.hxx"

#include "G4NistManager.hh"
#include "G4Polycone.hh"
#include "G4PVPlacement.hh"

using MACE::Core::Geometry::Entity::Fast::SpectrometerBody;
using namespace MACE::Utility::LiteralUnit::Density;

void SpectrometerBody::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerBody::Instance();
    const auto name = description.GetName();
    const auto shellInnerThickness = description.GetShellInnerThickness();
    const auto shellSideThickness = description.GetShellSideThickness();
    const auto shellOuterThickness = description.GetShellOuterThickness();
    const auto gasInnerRadius = description.GetGasInnerRadius();
    const auto gasOuterRadius = description.GetGasOuterRadius();
    const auto gasInnerLength = description.GetGasInnerLength();
    const auto gasOuterLength = description.GetGasOuterLength();

    auto shellMaterial = G4NistManager::Instance()->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);

    constexpr auto numZPlane = 4;
    const G4double zPlane[numZPlane] = {
        -gasOuterLength / 2 - shellSideThickness,
        -gasInnerLength / 2 - shellSideThickness,
        gasInnerLength / 2 + shellSideThickness,
        gasOuterLength / 2 + shellSideThickness};
    const G4double rInner[numZPlane] = {
        gasOuterRadius - shellInnerThickness,
        gasInnerRadius - shellInnerThickness,
        gasInnerRadius - shellInnerThickness,
        gasOuterRadius - shellInnerThickness};
    const G4double rOuter[numZPlane] = {
        gasOuterRadius + shellOuterThickness,
        gasOuterRadius + shellOuterThickness,
        gasOuterRadius + shellOuterThickness,
        gasOuterRadius + shellOuterThickness};

    auto solid = Make<G4Polycone>(
        name,
        0,
        2 * M_PI,
        numZPlane,
        zPlane,
        rInner,
        rOuter);
    auto logic = Make<G4LogicalVolume>(
        solid,
        shellMaterial,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
