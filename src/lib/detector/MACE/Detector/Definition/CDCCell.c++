#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Math/IntegerPower.h++"
#include "MACE/Math/Lerp.h++"
#include "MACE/Math/MidPoint.h++"
#include "MACE/Math/Parity.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/RotationZ.h"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4TwistedTubs.hh"
#include "G4TwoVector.hh"

#include <cmath>
#include <memory>
#include <utility>

namespace MACE::Detector::Definition {

auto CDCCell::Construct(G4bool checkOverlaps) -> void {
    using namespace MACE::LiteralUnit::MathConstantSuffix;

    const auto& cdc{Description::CDC::Instance()};
    const auto cellName{cdc.Name() + "Cell"};
    const auto fwName{cdc.Name() + "FieldWire"};
    const auto swName{cdc.Name() + "SenseWire"};

    const auto nist{G4NistManager::Instance()};

    for (auto&& super : std::as_const(cdc.LayerConfiguration())) {
        for (auto&& sense : super.sense) {
            //
            // cell volume
            //

            const auto cellRIn{sense.innerRadius};
            const auto cellROut{&sense != &super.sense.back() ?
                                    sense.outerRadius :
                                    sense.outerRadius + cdc.FieldWireDiameter()};
            const auto solidCell{[&, rFW{cdc.FieldWireDiameter() / 2}] {
                if (super.isAxial) {
                    return static_cast<G4VSolid*>(Make<G4Tubs>(
                        cellName,
                        cellRIn,
                        cellROut,
                        sense.halfLength,
                        -super.cellAzimuthWidth / 2,
                        super.cellAzimuthWidth));
                } else {
                    return static_cast<G4VSolid*>(Make<G4TwistedTubs>(
                        cellName,
                        sense.stereoAzimuthAngle,
                        cellRIn / std::cos(sense.stereoAzimuthAngle / 2),
                        cellROut / std::cos(sense.stereoAzimuthAngle / 2),
                        sense.halfLength,
                        super.cellAzimuthWidth));
                }
            }()};
            const auto logicalCell{Make<G4LogicalVolume>(
                solidCell,
                cdc.GasMaterial(),
                cellName)};
            const auto rFW{cdc.FieldWireDiameter() / 2};
            const auto phiHalfFW{std::asin(rFW / (cellRIn + rFW))};
            const auto phiOffset{2 * phiHalfFW}; // prevent protrusion
            Make<G4PVReplica>(cellName,
                              logicalCell,
                              Mother().LogicalVolume(sense.senseLayerID).get(),
                              kPhi,
                              super.nCellPerSenseLayer,
                              super.cellAzimuthWidth,
                              sense.cell.front().centerAzimuth - phiOffset);

            //
            // field wire volume
            //

            const auto solidFW{Make<G4Tubs>(
                fwName,
                0,
                rFW,
                sense.halfLength * sense.SecStereoZenithAngle(cellRIn) -
                    cdc.FieldWireDiameter(), // prevent protrusion
                0,
                2_pi)};
            const auto logicalFW{Make<G4LogicalVolume>(
                solidFW,
                nist->FindOrBuildMaterial("G4_Al"),
                fwName)};
            const auto PlaceFW{
                [&](int copyNo, double r, double phi0) {
                    return Make<G4PVPlacement>(
                        G4Transform3D{CLHEP::HepRotationZ{phi0 + phiOffset}, {}} *
                            G4Transform3D(CLHEP::HepRotationX(-sense.StereoZenithAngle(r)), {r, 0, 0}),
                        logicalFW,
                        fwName,
                        logicalCell,
                        false,
                        copyNo,
                        checkOverlaps);
                }};
            const auto rInnerWire{sense.innerRadius + rFW};
            const auto rOuterWire{sense.outerRadius + rFW};
            const auto rCenterWire{Math::MidPoint(rInnerWire, rOuterWire)};
            PlaceFW(0, rInnerWire, -super.cellAzimuthWidth / 2);
            PlaceFW(1, rInnerWire, 0);
            PlaceFW(2, rCenterWire, -super.cellAzimuthWidth / 2);
            if (&sense == &super.sense.back()) {
                PlaceFW(3, rOuterWire, -super.cellAzimuthWidth / 2);
                PlaceFW(4, rOuterWire, 0);
            }

            //
            // sense wire volume
            //

            const auto solidSW{Make<G4Tubs>(
                swName,
                0,
                cdc.SenseWireDiameter() / 2,
                sense.halfLength * sense.SecStereoZenithAngle(rCenterWire) -
                    cdc.SenseWireDiameter(), // prevent protrusion
                0,
                2_pi)};
            const auto logicalSW{Make<G4LogicalVolume>(
                solidSW,
                nist->FindOrBuildMaterial("G4_W"),
                swName)};
            Make<G4PVPlacement>(
                G4Transform3D{CLHEP::HepRotationZ{phiOffset}, {}} *
                    G4Transform3D(CLHEP::HepRotationX(-sense.StereoZenithAngle(rCenterWire)), {rCenterWire, 0, 0}),
                logicalSW,
                swName,
                logicalCell,
                false,
                sense.senseLayerID,
                checkOverlaps);
        }
    }
}

} // namespace MACE::Detector::Definition
