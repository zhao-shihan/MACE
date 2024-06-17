#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/SolenoidBeamPipe.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

#include "muc/math"

#include <cmath>

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit;

auto MCPChamber::Construct(G4bool checkOverlaps) -> void {
    const auto& mcpChamber{Description::MCPChamber::Instance()};
    const auto& solenoidBeamPipe{Description::SolenoidBeamPipe::Instance()};
    const auto& emcField{Description::EMCField::Instance()};

    const auto name{mcpChamber.Name()};

    const auto nist{G4NistManager::Instance()};

    { // Spherical chamber
        const auto solid{Make<G4SubtractionSolid>(
            name,
            Make<G4Sphere>(
                "_temp",
                mcpChamber.InnerRadius(),
                mcpChamber.InnerRadius() + mcpChamber.Thickness(),
                0,
                2_pi,
                0,
                1_pi),
            Make<G4Tubs>(
                "_temp",
                0,
                solenoidBeamPipe.InnerRadius(),
                mcpChamber.InnerRadius(),
                0,
                2_pi),
            nullptr,
            G4ThreeVector{0, 0, -mcpChamber.InnerRadius()})};

        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->FindOrBuildMaterial("G4_Be"),
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

    { // Pipe
        const auto radiusCos{mcpChamber.InnerRadius() * std::sqrt(1 - muc::pow<2>(solenoidBeamPipe.InnerRadius() / mcpChamber.InnerRadius()))};
        const auto halfLength{(emcField.Length() / 2 - radiusCos) / 2};

        const auto solid{Make<G4Tubs>(
            name,
            solenoidBeamPipe.InnerRadius() - mcpChamber.Thickness(),
            solenoidBeamPipe.InnerRadius(),
            halfLength,
            0,
            2_pi)};

        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->FindOrBuildMaterial("G4_Al"),
            name)};

        Make<G4PVPlacement>(
            G4TranslateZ3D{-halfLength - radiusCos},
            logic,
            name,
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Definition
