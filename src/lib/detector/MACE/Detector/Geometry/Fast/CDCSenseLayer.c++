#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseLayer.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Hype.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "gsl/gsl"

#include <utility>

namespace MACE::Detector::Geometry::Fast {

void CDCSenseLayer::Construct(G4bool checkOverlaps) {
    using namespace MACE::LiteralUnit::MathConstantSuffix;

    const auto& cdc = Description::CDC::Instance();
    const auto name = "CDCSenseLayer";

    for (auto&& super : std::as_const(cdc.LayerConfiguration())) {
        for (auto&& sense : super.sense) {
            const auto layerInnerRadius = sense.innerRadius;
            const auto layerOuterRadius = &sense != &super.sense.back() ?
                                              sense.outerRadius :
                                              sense.outerRadius + cdc.FieldWireDiameter();
            const auto solid =
                super.isAxial ?
                    static_cast<G4VSolid*>(Make<G4Tubs>(
                        name,
                        layerInnerRadius,
                        layerOuterRadius,
                        sense.halfLength,
                        0,
                        2_pi)) :
                    static_cast<G4VSolid*>(Make<G4Hype>(
                        name,
                        layerInnerRadius,
                        layerOuterRadius,
                        sense.StereoZenithAngle(layerInnerRadius),
                        sense.StereoZenithAngle(layerOuterRadius),
                        sense.halfLength));
            const auto logic = Make<G4LogicalVolume>(
                solid,
                nullptr,
                name);
            Make<G4PVPlacement>(
                G4Transform3D(),
                logic,
                name,
                Mother().LogicalVolume(super.superLayerID).get(),
                false,
                sense.senseLayerID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Detector::Geometry::Fast
