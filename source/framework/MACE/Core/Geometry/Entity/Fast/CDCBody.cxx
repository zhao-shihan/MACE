#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCBody.hxx"
#include "MACE/Math/IntegerPower.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"
#include "G4Polycone.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include <array>
#include <cmath>

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::LiteralUnit::MathConstant;

void CDCBody::Construct(G4bool checkOverlaps) {
    const auto& cdc = Description::CDC::Instance();
    const auto name = "CDCBody";
    const auto sideExtension = cdc.ShellSideThickness() * std::sqrt(1 + 1 / Math::Pow2(cdc.EndCapSlope())) -
                               cdc.ShellInnerThickness() / cdc.EndCapSlope();
    const auto zI = cdc.GasInnerLength() / 2 + sideExtension;
    const auto zO = cdc.GasOuterLength() / 2 + sideExtension;
    const auto rI = cdc.GasInnerRadius() - cdc.ShellInnerThickness();
    const auto rOI = cdc.GasOuterRadius() - cdc.ShellInnerThickness();
    const auto rOO = cdc.GasOuterRadius() + cdc.ShellOuterThickness();

    const std::array zPlaneList = {-zO, -zI, zI, zO};
    const std::array rInnerList = {rOI, rI, rI, rOI};
    const std::array rOuterList = {rOO, rOO, rOO, rOO};

    const auto solid = Make<G4Polycone>(
        name,
        0,
        2_pi,
        zPlaneList.size(),
        zPlaneList.data(),
        rInnerList.data(),
        rOuterList.data());
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
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

} // namespace MACE::Core::Geometry::Entity::Fast
