#include "MACE/Detector/Definition/SpectrometerBeamPipe.h++"
#include "MACE/Detector/Description/SpectrometerBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SpectrometerBeamPipe::Construct(G4bool checkOverlaps) -> void {
    const auto& beamPipe{Description::SpectrometerBeamPipe::Instance()};

    const auto solid{Make<G4Tubs>(
        beamPipe.Name(),
        beamPipe.InnerRadius(),
        beamPipe.InnerRadius() + beamPipe.Thickness(),
        beamPipe.Length() / 2,
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

} // namespace MACE::Detector::Definition
