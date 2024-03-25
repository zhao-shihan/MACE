#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto MMSBeamPipe::Construct(G4bool checkOverlaps) -> void {
    const auto& beamPipe{Description::MMSBeamPipe::Instance()};
    const auto& mmsField{Description::MMSField::Instance()};

    { // Beryllium pipe section
        const auto solid{Make<G4Tubs>(
            beamPipe.Name(),
            beamPipe.InnerRadius(),
            beamPipe.InnerRadius() + beamPipe.BerylliumThickness(),
            beamPipe.BerylliumLength() / 2,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            G4NistManager::Instance()->FindOrBuildMaterial("G4_Be"),
            beamPipe.Name())};
        Make<G4PVPlacement>(
            G4Transform3D{},
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    { // Aluminium pipe section
        const auto solid{Make<G4Tubs>(
            beamPipe.Name(),
            beamPipe.InnerRadius(),
            beamPipe.InnerRadius() + beamPipe.AluminiumThickness(),
            (mmsField.Length() - beamPipe.BerylliumLength()) / 4,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"),
            beamPipe.Name())};
        const auto z0{(mmsField.Length() + beamPipe.BerylliumLength()) / 4};
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {0, 0, -z0}}, // clang-format on
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {0, 0, z0}}, // clang-format on
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
