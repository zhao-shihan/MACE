#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SolenoidBeamPipe.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorC.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorC.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"

namespace MACE::SimPTS::Detector::Definition {

auto VirtualDetectorC::Construct(bool checkOverlaps) -> void {
    const auto& solenoid{MACE::Detector::Description::Solenoid::Instance()};
    const auto& solenoidBeamPipe{MACE::Detector::Description::SolenoidBeamPipe::Instance()};
    const auto& virtualDetectorC{Description::VirtualDetectorC::Instance()};

    const auto mother{Mother().LogicalVolume("SolenoidBeamPipeS2Vacuum")};
    const auto solid{Make<G4Tubs>(
        virtualDetectorC.Name(),
        0,
        solenoidBeamPipe.InnerRadius(),
        virtualDetectorC.Thickness() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        mother->GetMaterial(),
        virtualDetectorC.Name())};
    Make<G4PVPlacement>(
        G4TranslateZ3D{solenoid.S2Length() / 2 - virtualDetectorC.Thickness() / 2},
        logic,
        virtualDetectorC.Name(),
        mother,
        false,
        2,
        checkOverlaps);
}

} // namespace MACE::SimPTS::Detector::Definition
