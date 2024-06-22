#pragma once

#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorA.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorB.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorC.h++"
#include "MACE/SimPTS/Detector/Description/VirtualDetectorD.h++"
#include "MACE/SimPTS/Region.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE::SimPTS {

inline namespace SD {
class VirtualSD;
} // namespace SD

inline namespace Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto DefaultGaseousRegion() const -> const auto& { return *fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return *fDefaultSolidRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto SolenoidOrMagnetRegion() const -> const auto& { return *fSolenoidOrMagnetRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }

    auto VirtualSD() const -> auto& { return *fVirtualSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::VirtualDetectorA,
                                        Detector::Description::VirtualDetectorB,
                                        Detector::Description::VirtualDetectorC,
                                        Detector::Description::VirtualDetectorD,
                                        MACE::Detector::Description::Accelerator,
                                        MACE::Detector::Description::EMCField,
                                        MACE::Detector::Description::EMCMagnet,
                                        MACE::Detector::Description::EMCShield,
                                        MACE::Detector::Description::FieldOption,
                                        MACE::Detector::Description::Filter,
                                        MACE::Detector::Description::MCPChamber,
                                        MACE::Detector::Description::MMSBeamPipe,
                                        MACE::Detector::Description::MMSField,
                                        MACE::Detector::Description::MMSMagnet,
                                        MACE::Detector::Description::MMSShield,
                                        MACE::Detector::Description::ShieldingWall,
                                        MACE::Detector::Description::Solenoid,
                                        MACE::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fVacuumRegion;

    SD::VirtualSD* fVirtualSD;
};

} // namespace Action

} // namespace MACE::SimPTS
