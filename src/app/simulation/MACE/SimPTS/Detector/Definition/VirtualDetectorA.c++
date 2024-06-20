#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorA.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorA.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::SimPTS::Detector::Definition {

using namespace Mustard::LiteralUnit::MathConstantSuffix;

auto VirtualDetectorA::Construct(bool checkOverlaps) -> void {
    const auto& accelerator{MACE::Detector::Description::Accelerator::Instance()};
    const auto& mmsBeamPipe{MACE::Detector::Description::MMSBeamPipe::Instance()};
    const auto& virtualDetectorA{Description::VirtualDetectorA::Instance()};

    const auto solid{Make<G4Tubs>(
        virtualDetectorA.Name(),
        0,
        mmsBeamPipe.InnerRadius(),
        virtualDetectorA.Thickness() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        Mother().LogicalVolume()->GetMaterial(),
        virtualDetectorA.Name())};
    Make<G4PVPlacement>(
        G4TranslateZ3D{accelerator.AccelerateLength() + virtualDetectorA.Thickness() / 2},
        logic,
        virtualDetectorA.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::SimPTS::Detector::Definition
