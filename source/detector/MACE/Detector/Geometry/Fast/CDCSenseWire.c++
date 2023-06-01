#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseWire.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationX.h"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "gsl/gsl"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::Length;
using namespace MACE::LiteralUnit::MathConstant;

void CDCSenseWire::Construct(G4bool checkOverlaps) {
    const auto name = "CDCSenseWire";
    const auto& cdc = Description::CDC::Instance();
    const auto rSenseWire = cdc.SenseWireDiameter() / 2;
    const auto& cellMap = cdc.CellMap();

    for (auto&& super : std::as_const(cdc.LayerConfiguration())) {
        for (auto&& sense : super.sense) {
            const auto typicalCellID = sense.cell[super.nCellPerSenseLayer / 8].cellID;
            const auto wireRadialPosition = cellMap[typicalCellID].position.norm();

            const auto solid = Make<G4Tubs>(
                name,
                0,
                rSenseWire,
                sense.halfLength * sense.SecStereoZenithAngle(wireRadialPosition) -
                    cdc.SenseWireDiameter(), // prevent protrusion
                0,
                2_pi);
            const auto logic = Make<G4LogicalVolume>(
                solid,
                nullptr,
                name);
            Make<G4PVPlacement>(
                G4Transform3D(CLHEP::HepRotationX(-sense.StereoZenithAngle(wireRadialPosition)),
                              {wireRadialPosition, 0, 0}),
                logic,
                name,
                Mother().LogicalVolume(sense.senseLayerID).get(),
                false,
                sense.senseLayerID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Detector::Geometry::Fast
