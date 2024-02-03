#pragma once

#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Region.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector::Definition {

class GeometryBase;

} // namespace Detector::Definition

namespace SimEMC::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto EMCSensitiveRegion() const -> const auto& { return *fEMCSensitiveRegion; }
    auto MCPSensitiveRegion() const -> const auto& { return *fMCPSensitiveRegion; }
    auto ShieldRegion() const -> const auto& { return *fShieldRegion; }
    auto TunnelRegion() const -> const auto& { return *fTunnelRegion; }
    auto VacuumRegion() const -> const auto& { return *fVacuumRegion; }

    auto EMCSD() const -> auto& { return *fEMCSD; }
    auto EMCPMTSD() const -> auto& { return *fEMCPMTSD; }
    auto MCPSD() const -> auto& { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::EMC,
                                        MACE::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<MACE::Detector::Definition::GeometryBase> fWorld;

    Region* fEMCSensitiveRegion;
    Region* fMCPSensitiveRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fShieldRegion;
    Region* fTunnelRegion;
    Region* fVacuumRegion;

    SD::EMCSD* fEMCSD;
    SD::EMCPMTSD* fEMCPMTSD;
    SD::MCPSD* fMCPSD;
};

} // namespace SimEMC::inline Action

} // namespace MACE
