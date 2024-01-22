#pragma once

#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Region.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"
#include "MACE/SimEMC/SD/PMTSD.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace MACE {

namespace Detector::Geometry {

class GeometryBase;

} // namespace Detector::Geometry

namespace SimEMC::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto EMCSensitiveRegion() const -> auto& { return *fEMCSensitiveRegion; }
    auto MCPSensitiveRegion() const -> auto& { return *fMCPSensitiveRegion; }
    auto ShieldRegion() const -> auto& { return *fShieldRegion; }
    auto TunnelRegion() const -> auto& { return *fTunnelRegion; }
    auto VacuumRegion() const -> auto& { return *fVacuumRegion; }

    auto EMCSD() const -> auto& { return *fEMCSD; }
    auto PMTSD() const -> auto& { return *fPMTSD; }
    auto MCPSD() const -> auto& { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<MACE::Detector::Description::EMC,
                                        MACE::Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<MACE::Detector::Geometry::GeometryBase> fWorld;

    Region* fEMCSensitiveRegion;
    Region* fMCPSensitiveRegion;
    Region* fShieldRegion;
    Region* fTunnelRegion;
    Region* fVacuumRegion;

    SD::EMCSD* fEMCSD;
    SD::PMTSD* fPMTSD;
    SD::MCPSD* fMCPSD;
};

} // namespace SimEMC::inline Action

} // namespace MACE
