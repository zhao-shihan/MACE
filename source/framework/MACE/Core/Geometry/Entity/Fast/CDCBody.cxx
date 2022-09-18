#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCBody.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4Polycone.hh"
#include "G4PVPlacement.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::LiteralUnit::Density;
using namespace MACE::Utility::PhysicalConstant;

void CDCBody::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CDC::Instance();
    const auto name = "CDCBody";
    const auto shellInnerThickness = description.ShellInnerThickness();
    const auto shellSideThickness = description.ShellSideThickness();
    const auto shellOuterThickness = description.ShellOuterThickness();
    const auto gasInnerRadius = description.GasInnerRadius();
    const auto gasOuterRadius = description.GasOuterRadius();
    const auto gasInnerLength = description.GasInnerLength();
    const auto gasOuterLength = description.GasOuterLength();

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
        twopi,
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
        Mother()->LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
