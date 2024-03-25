#pragma once

#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/STC.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Region.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE {

namespace Detector::Definition {
class DefinitionBase;
} // namespace Detector::Definition

namespace SimMACE {

inline namespace SD {
class CDCSD;
class EMCSD;
class MCPSD;
class STCSD;
} // namespace SD

inline namespace Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto CDCSensitiveRegion() const -> const auto& { return *fCDCSensitiveRegion; }
    auto DefaultGaseousRegion() const -> const auto& { return *fDefaultGaseousRegion; }
    auto DefaultSolidRegion() const -> const auto& { return *fDefaultSolidRegion; }
    auto EMCSensitiveRegion() const -> const auto& { return *fEMCSensitiveRegion; }
    auto MCPSensitiveRegion() const -> const auto& { return *fMCPSensitiveRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto SolenoidOrMagnetRegion() const -> const auto& { return *fSolenoidOrMagnetRegion; }
    auto TargetRegion() const -> const auto& { return *fTargetRegion; }
    auto STCSensitiveRegion() const -> const auto& { return *fSTCSensitiveRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }

    auto CDCSD() const -> auto& { return *fCDCSD; }
    auto STCSD() const -> auto& { return *fSTCSD; }
    auto MCPSD() const -> auto& { return *fMCPSD; }
    auto EMCSD() const -> auto& { return *fEMCSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::AcceleratorField,
                                        Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::EMC,
                                        Detector::Description::EMCField,
                                        Detector::Description::EMCMagnet,
                                        Detector::Description::EMCShield,
                                        Detector::Description::Filter,
                                        Detector::Description::MCP,
                                        Detector::Description::MCPChamber,
                                        Detector::Description::MMSBeamPipe,
                                        Detector::Description::MMSField,
                                        Detector::Description::MMSMagnet,
                                        Detector::Description::MMSShield,
                                        Detector::Description::ShieldingWall,
                                        Detector::Description::Solenoid,
                                        Detector::Description::STC,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Detector::Definition::DefinitionBase> fWorld;

    Region* fCDCFieldWireRegion;
    Region* fCDCSenseWireRegion;
    Region* fCDCSensitiveRegion;
    Region* fDefaultGaseousRegion;
    Region* fDefaultSolidRegion;
    Region* fEMCSensitiveRegion;
    Region* fMCPSensitiveRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fSTCSensitiveRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::CDCSD* fCDCSD;
    SD::STCSD* fSTCSD;
    SD::MCPSD* fMCPSD;
    SD::EMCSD* fEMCSD;
};

} // namespace Action

} // namespace SimMACE

} // namespace MACE
