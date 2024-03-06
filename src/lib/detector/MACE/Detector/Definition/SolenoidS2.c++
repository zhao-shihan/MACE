#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidS2::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "S1"};

    auto solid{Make<G4Tubs>(
        name,
        solenoid.InnerRadius(),
        solenoid.OuterRadius(),
        solenoid.S2Length() / 2,
        0,
        2_pi)};
    auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(solenoid.MaterialName()),
        name)};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
