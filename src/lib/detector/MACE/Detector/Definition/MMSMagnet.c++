#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto MMSMagnet::Construct(G4bool checkOverlaps) -> void {
    const auto& magnet{Description::MMSMagnet::Instance()};

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
