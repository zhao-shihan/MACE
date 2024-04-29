#include "MACE/PhaseI/Detector/Definition/CentralBeamPipe.h++"
#include "MACE/PhaseI/Detector/Description/CentralBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::PhaseI::Detector::Definition {

using namespace LiteralUnit::MathConstantSuffix;
using namespace PhysicalConstant;

auto CentralBeamPipe::Construct(G4bool checkOverlaps) -> void {
    const auto& beamPipe{Description::CentralBeamPipe::Instance()};

    const auto nist{G4NistManager::Instance()};

    { // Beryllium pipe section
        const auto solid{Make<G4Tubs>(
            beamPipe.Name(),
            beamPipe.InnerRadius(),
            beamPipe.InnerRadius() + beamPipe.BerylliumThickness(),
            beamPipe.BerylliumLength() / 2,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->FindOrBuildMaterial("G4_Be"),
            beamPipe.Name())};
        Make<G4PVPlacement>(
            G4Transform3D{},
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    { // Aluminium pipe section
        const auto solid{Make<G4Tubs>(
            beamPipe.Name(),
            beamPipe.InnerRadius(),
            beamPipe.InnerRadius() + beamPipe.AluminiumThickness(),
            (beamPipe.Length() - beamPipe.BerylliumLength()) / 4,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            nist->FindOrBuildMaterial("G4_Al"),
            beamPipe.Name())};
        const auto z0{(beamPipe.Length() + beamPipe.BerylliumLength()) / 4};
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {0, 0, -z0}}, // clang-format on
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
        Make<G4PVPlacement>( // clang-format off
            G4Transform3D{{}, {0, 0, z0}}, // clang-format on
            logic,
            beamPipe.Name(),
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
    { // Vacuum
        const auto vacuumName{beamPipe.Name() + "Vacuum"};
        const auto air{nist->FindOrBuildMaterial("G4_AIR")};
        const auto density{beamPipe.VacuumPressure() * air->GetMassOfMolecule() / (k_Boltzmann * STP_Temperature)};
        const auto vacuum{nist->BuildMaterialWithNewDensity(vacuumName, "G4_AIR", density, STP_Temperature, beamPipe.VacuumPressure())};

        const auto solid{Make<G4Tubs>(
            vacuumName,
            0,
            beamPipe.InnerRadius(),
            beamPipe.Length() / 2,
            0,
            2_pi)};
        const auto logic{Make<G4LogicalVolume>(
            solid,
            vacuum,
            vacuumName)};
        Make<G4PVPlacement>(
            G4Transform3D{},
            logic,
            vacuumName,
            Mother().LogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::PhaseI::Detector::Definition
