#include "MACE/Detector/Definition/SpectrometerMagnet.h++"
#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;

auto SpectrometerMagnet::Construct(G4bool checkOverlaps) -> void {
    const auto& magnet{Description::SpectrometerMagnet::Instance()};

    auto solid{Make<G4Tubs>(
        magnet.Name(),
        magnet.InnerRadius(),
        magnet.OuterRadius(),
        magnet.Length() / 2,
        0,
        2_pi)};
    auto logic = Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(magnet.MaterialName()),
        magnet.Name());
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        magnet.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
