#include "MACE/Detector/Description/ECalMagnet.h++"
#include "MACE/SimECal/Detector/ECalMagnet.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::SimECal::Detector {

using namespace Mustard::LiteralUnit;

auto ECalMagnet::Construct(G4bool checkOverlaps) -> void {
    const auto& magnet{MACE::Detector::Description::ECalMagnet::Instance()};

    const auto solid{Make<G4Tubs>(
        magnet.Name(),
        magnet.InnerRadius(),
        magnet.OuterRadius(),
        magnet.Length() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(magnet.MaterialName()),
        magnet.Name())};
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        magnet.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::SimECal::Detector
