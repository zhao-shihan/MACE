#include "MACE/Core/Geometry/Description/CDC.hxx"
#include "MACE/Core/Geometry/Entity/Fast/CDCCell.hxx"
#include "MACE/Math/Lerp.hxx"
#include "MACE/Math/Parity.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/VectorCast.hxx"

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

namespace MACE::Core::Geometry::Entity::Fast {

void CDCCell::Construct(G4bool checkOverlaps) {
    using namespace MACE::Utility::LiteralUnit::MathConstant;

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
                    if (super.isAxial) {
                        return static_cast<G4VSolid*>(Make<G4Tubs>(
                            name,
                            rIn,
                            rOut,
                            sense.halfLength,
                            0,
                            2_pi));
                    } else {
                        const auto secHalfPhiS = 1 / std::cos(sense.stereoAzimuthAngle / 2);
                        return static_cast<G4VSolid*>(Make<G4TwistedTubs>(
                            name,
                            sense.stereoAzimuthAngle,
                            rIn * secHalfPhiS,
                            rOut * secHalfPhiS,
                            sense.halfLength,
                            cdc.SensitiveWidthFactor() * super.cellAzimuthWidth));
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

} // namespace MACE::Core::Geometry::Entity::Fast
