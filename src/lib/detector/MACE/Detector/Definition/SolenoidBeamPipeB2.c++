#include "MACE/Detector/Definition/SolenoidBeamPipeB2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SolenoidBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidBeamPipeB2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& beamPipe{Description::SolenoidBeamPipe::Instance()};
    const auto name{beamPipe.Name() + "B2"};

    const auto solid{Make<G4Torus>(
        name,
        beamPipe.InnerRadius(),
        beamPipe.InnerRadius() + beamPipe.Thickness(),
        solenoid.B2Radius(),
        0,
        0.5_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(beamPipe.MaterialName()),
        name)};

    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        name,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
