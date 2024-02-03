#pragma once

#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Region.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE {

namespace Detector::Definition {

class DefinitionBase;

} // namespace Detector::Definition

namespace SimMACE::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto EMCSensitiveRegion() const -> const auto& { return *fEMCSensitiveRegion; }
    auto DefaultSolidRegion() const -> const auto& { return *fDefaultSolidRegion; }
    auto DefaultGaseousRegion() const -> const auto& { return *fDefaultGaseousRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto SolenoidOrMagnetRegion() const -> const auto& { return *fSolenoidOrMagnetRegion; }
    auto SpectrometerSensitiveRegion() const -> const auto& { return *fSpectrometerSensitiveRegion; }
    auto TargetRegion() const -> const auto& { return *fTargetRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }
    auto MCPSensitiveRegion() const -> const auto& { return *fMCPSensitiveRegion; }

    auto EMCSD() const -> auto& { return *fEMCSD; }
    auto CDCSD() const -> auto& { return *fCDCSD; }
    auto MCPSD() const -> auto& { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::AcceleratorField,
                                        Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::EMC,
                                        Detector::Description::EMCField,
                                        Detector::Description::EMCShield,
                                        Detector::Description::Filter,
                                        Detector::Description::MCP,
                                        Detector::Description::ShieldingWall,
                                        Detector::Description::Solenoid,
                                        Detector::Description::SpectrometerField,
                                        Detector::Description::SpectrometerMagnet,
                                        Detector::Description::SpectrometerShield,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Detector::Definition::DefinitionBase> fWorld;

    Region* fCDCFieldWireRegion;
    Region* fCDCSenseWireRegion;
    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fEMCSensitiveRegion;
    Region* fMCPSensitiveRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fSpectrometerSensitiveRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::CDCSD* fCDCSD;
    SD::EMCSD* fEMCSD;
    SD::MCPSD* fMCPSD;
};

} // namespace SimMACE::inline Action

} // namespace MACE
