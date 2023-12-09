#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Geometry/Fast/CDCCell.h++"
#include "MACE/Math/Lerp.h++"
#include "MACE/Math/Parity.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4TwistedTubs.hh"
#include "G4TwoVector.hh"

#include "gsl/gsl"

#include <cmath>
#include <memory>
#include <utility>

namespace MACE::Detector::Geometry::Fast {

auto CDCCell::Construct(G4bool checkOverlaps) -> void {
    using namespace MACE::LiteralUnit::MathConstantSuffix;

    const auto name = "CDCCell";
    const auto& cdc = Description::CDC::Instance();

    for (auto&& super : std::as_const(cdc.LayerConfiguration())) {
        for (auto&& sense : super.sense) {
            const auto Solid =
                [&,
                 rFW = cdc.FieldWireDiameter() / 2,
                 halfWidthCorrection = (1 - cdc.SensitiveWidthFactor()) * sense.cellWidth / 2] {
                    const auto rIn = sense.innerRadius + rFW + halfWidthCorrection;
                    const auto rOut = sense.outerRadius + rFW - halfWidthCorrection;
                    const auto senseWidth = cdc.SensitiveWidthFactor() * super.cellAzimuthWidth;
                    if (super.isAxial) {
                        return static_cast<G4VSolid*>(Make<G4Tubs>(
                            name,
                            rIn,
                            rOut,
                            sense.halfLength,
                            -senseWidth / 2,
                            senseWidth));
                    } else {
                        const auto secHalfPhiS = 1 / std::cos(sense.stereoAzimuthAngle / 2);
                        return static_cast<G4VSolid*>(Make<G4TwistedTubs>(
                            name,
                            sense.stereoAzimuthAngle,
                            rIn * secHalfPhiS,
                            rOut * secHalfPhiS,
                            sense.halfLength,
                            senseWidth));
                    }
                };
            const auto logic = Make<G4LogicalVolume>(
                Solid(),
                nullptr,
                name);
            for (auto&& cell : sense.cell) {
                Make<G4PVPlacement>(
                    G4Transform3D(CLHEP::HepRotationZ(cell.centerAzimuth),
                                  {0, 0, 0}),
                    logic,
                    name,
                    Mother().LogicalVolume(sense.senseLayerID).get(),
                    false,
                    cell.cellID,
                    checkOverlaps);
            }
        }
    }
}

} // namespace MACE::Detector::Geometry::Fast
