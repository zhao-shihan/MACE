#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::SimEMC::Detector {

using namespace LiteralUnit;

auto EMCMagnet::Construct(G4bool checkOverlaps) -> void {
    const auto& magnet{MACE::Detector::Description::EMCMagnet::Instance()};

    const auto nist = G4NistManager::Instance();
    const auto copper = nist->FindOrBuildMaterial("G4_Cu");

    const auto solid{Make<G4Tubs>(
        magnet.Name(),
        magnet.InnerRadius(),
        magnet.OuterRadius(),
        magnet.Length() / 2,
        0,
        2_pi)};

    const auto logic{Make<G4LogicalVolume>(
        solid,
        copper,
        magnet.Name())};

    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        magnet.Name(),
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::SimEMC::Detector
