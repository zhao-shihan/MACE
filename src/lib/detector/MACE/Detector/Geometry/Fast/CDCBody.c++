#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Geometry/Fast/CDCBody.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4Polycone.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include <array>
#include <cmath>

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::MathConstantSuffix;

void CDCBody::Construct(G4bool checkOverlaps) {
    const auto& cdc = Description::CDC::Instance();
    const auto name = "CDCBody";
    const auto sideExtension = cdc.ShellSideThickness() * std::sqrt(1 + 1 / Math::Pow<2>(cdc.EndCapSlope())) -
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

} // namespace MACE::Detector::Geometry::Fast
