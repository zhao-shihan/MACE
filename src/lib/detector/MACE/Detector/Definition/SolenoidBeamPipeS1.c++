#include "MACE/Detector/Definition/SolenoidBeamPipeS1.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SolenoidBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidBeamPipeS1::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& beamPipe{Description::SolenoidBeamPipe::Instance()};
    const auto name{beamPipe.Name() + "S1"};

    const auto solid{Make<G4Tubs>(
        name,
        beamPipe.InnerRadius(),
        beamPipe.InnerRadius() + beamPipe.Thickness(),
        solenoid.S1Length() / 2,
        0,
        2_pi)};

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
