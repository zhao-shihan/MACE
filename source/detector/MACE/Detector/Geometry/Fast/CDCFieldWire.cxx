#include "MACE/Detector/Description/CDC.hxx"
#include "MACE/Detector/Geometry/Fast/CDCFieldWire.hxx"
#include "MACE/Math/IntegerPower.hxx"
#include "MACE/Math/MidPoint.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/RotationX.h"
#include "CLHEP/Vector/RotationZ.h"

#include "G4GenericTrap.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include <utility>

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::LiteralUnit::Length;
using namespace MACE::LiteralUnit::MathConstant;

void CDCFieldWire::Construct(G4bool checkOverlaps) {
    const auto name = "CDCFieldWire";
    const auto& cdc = Description::CDC::Instance();
    const auto rFieldWire = cdc.FieldWireDiameter() / 2;

    for (int fieldWireID = 0;
         auto&& super : std::as_const(cdc.LayerConfiguration())) {
        const auto halfPhiCell = super.cellAzimuthWidth / 2;

        for (auto&& sense : super.sense) {
            const auto MakeFieldWirePlacement =
                [&](const auto rWireInner) {
                    const auto r = rWireInner + rFieldWire;
                    const auto solid = Make<G4Tubs>(
                        name,
                        0,
                        rFieldWire,
                        sense.halfLength * sense.SecStereoZenithAngle(r) -
                            cdc.FieldWireDiameter(), // prevent protrusion
                        0,
                        2_pi);
                    const auto logic = Make<G4LogicalVolume>(
                        solid,
                        nullptr,
                        name);
                    return
                        [&, logic,
                         motherLogicalVolume = Mother().LogicalVolume(sense.senseLayerID).get(),
                         initialTransform = G4Transform3D(CLHEP::HepRotationX(-sense.StereoZenithAngle(r)),
                                                          {r, 0, 0})](const auto phi) {
                            Make<G4PVPlacement>(
                                G4Transform3D(CLHEP::HepRotationZ(phi), {0, 0, 0}) * initialTransform,
                                logic,
                                name,
                                motherLogicalVolume,
                                false,
                                fieldWireID++,
                                checkOverlaps);
                        };
                };

            const auto PlaceInnerFieldWire = MakeFieldWirePlacement(sense.innerRadius);
            for (auto&& cell : sense.cell) {
                PlaceInnerFieldWire(cell.centerAzimuth - halfPhiCell);
                PlaceInnerFieldWire(cell.centerAzimuth);
            }

            const auto PlaceCenterFieldWire = MakeFieldWirePlacement(Math::MidPoint(sense.innerRadius, sense.outerRadius));
            for (auto&& cell : sense.cell) {
                PlaceCenterFieldWire(cell.centerAzimuth - halfPhiCell);
            }

            if (&sense == &super.sense.back()) {
                const auto PlaceOuterFieldWire = MakeFieldWirePlacement(sense.outerRadius);
                for (auto&& cell : sense.cell) {
                    PlaceOuterFieldWire(cell.centerAzimuth - halfPhiCell);
                    PlaceOuterFieldWire(cell.centerAzimuth);
                }
            }
        }
    }
}

} // namespace MACE::Detector::Geometry::Fast
