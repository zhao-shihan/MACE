#include "MACE/Detector/Definition/SolenoidBeamPipeS3.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SolenoidBeamPipe.h++"
#include "MACE/Detector/Description/Vacuum.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;
using namespace Mustard::LiteralUnit::Temperature;

auto SolenoidBeamPipeS3::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto& beamPipe{Description::SolenoidBeamPipe::Instance()};
    const auto& vacuum{Description::Vacuum::Instance()};

    const auto nist{G4NistManager::Instance()};
    auto vacuumMaterial{nist->FindMaterial(vacuum.Name())};
    if (not vacuumMaterial) {
        vacuumMaterial = nist->BuildMaterialWithNewDensity(vacuum.Name(), "G4_AIR", vacuum.Density(), 293.15_K, vacuum.Pressure());
    }

    const auto pipeName{beamPipe.Name() + "S3"};
    const auto solidPipe{Make<G4Tubs>(
        pipeName,
        0,
        beamPipe.InnerRadius() + beamPipe.Thickness(),
        solenoid.S3Length() / 2,
        0,
        2_pi)};
    const auto logicPipe{Make<G4LogicalVolume>(
        solidPipe,
        G4NistManager::Instance()->FindOrBuildMaterial(beamPipe.MaterialName()),
        pipeName)};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logicPipe,
        pipeName,
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);

    const auto vacuumName{pipeName + "Vacuum"};
    const auto solidVacuum{Make<G4Tubs>(
        vacuumName,
        0,
        beamPipe.InnerRadius(),
        solidPipe->GetZHalfLength(),
        0,
        2_pi)};
    const auto logicVacuum{Make<G4LogicalVolume>(
        solidVacuum,
        vacuumMaterial,
        vacuumName)};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logicVacuum,
        vacuumName,
        logicPipe,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
