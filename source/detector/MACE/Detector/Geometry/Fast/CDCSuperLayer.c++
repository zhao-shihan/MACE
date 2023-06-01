#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Geometry/Fast/CDCSuperLayer.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Polycone.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"

#include "gsl/gsl"

#include <array>

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::MathConstant;

void CDCSuperLayer::Construct(G4bool checkOverlaps) {
    const auto& cdc = Description::CDC::Instance();
    const auto name = "CDCSuperLayer";
    const auto layerConfig = cdc.LayerConfiguration();

    for (gsl::index superLayerID = 0; superLayerID < cdc.NSuperLayer(); ++superLayerID) {
        const auto& super = layerConfig[superLayerID];

        const auto zI = super.innerHalfLength;
        const auto zO = super.outerHalfLength;
        const auto rI = super.innerRadius;
        const auto rO = super.outerRadius;

        const std::array zPlaneList = {-zO, -zI, zI, zO};
        const std::array rInnerList = {rO, rI, rI, rO};
        const std::array rOuterList = {rO, rO, rO, rO};

        const auto solid = Make<G4Polycone>(
            name,
            0,
            2_pi,
            zPlaneList.size(),
            zPlaneList.data(),
            rInnerList.data(),
            rOuterList.data());
        const auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(),
            logic,
            name,
            Mother().LogicalVolume().get(),
            false,
            superLayerID,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Geometry::Fast
