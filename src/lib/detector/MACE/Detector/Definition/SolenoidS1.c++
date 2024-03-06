#include "MACE/Detector/Definition/SolenoidS1.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SolenoidS1::Construct(G4bool checkOverlaps) -> void {
    const auto& solenoid{Description::Solenoid::Instance()};
    const auto name{solenoid.Name() + "S1"};

    const auto solid{Make<G4Tubs>(
        name,
        solenoid.InnerRadius(),
        solenoid.OuterRadius(),
        solenoid.S1Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
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
