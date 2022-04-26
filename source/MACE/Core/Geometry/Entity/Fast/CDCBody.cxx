#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCBody.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"
#include "G4Polycone.hh"
#include "G4PVPlacement.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::LiteralUnit::Density;

void CDCBody::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCBody";
    const auto shellInnerThickness = description.GetShellInnerThickness();
    const auto shellSideThickness = description.GetShellSideThickness();
    const auto shellOuterThickness = description.GetShellOuterThickness();
    const auto gasInnerRadius = description.GetGasInnerRadius();
    const auto gasOuterRadius = description.GetGasOuterRadius();
    const auto gasInnerLength = description.GetGasInnerLength();
    const auto gasOuterLength = description.GetGasOuterLength();

    constexpr auto numZPlane = 4;
    const G4double zPlane[numZPlane] = {-gasOuterLength / 2 - shellSideThickness,
                                        -gasInnerLength / 2 - shellSideThickness,
                                        gasInnerLength / 2 + shellSideThickness,
                                        gasOuterLength / 2 + shellSideThickness};
    const G4double rInner[numZPlane] = {gasOuterRadius - shellInnerThickness,
                                        gasInnerRadius - shellInnerThickness,
                                        gasInnerRadius - shellInnerThickness,
                                        gasOuterRadius - shellInnerThickness};
    const G4double rOuter[numZPlane] = {gasOuterRadius + shellOuterThickness,
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
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
