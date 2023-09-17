#pragma once

#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/MultiplateCollimator.h++"
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

namespace Detector::Geometry {

class GeometryBase;

} // namespace Detector::Geometry

namespace SimMACE::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

    auto& EMCSensitiveRegion() const { return *fEMCSensitiveRegion; }
    auto& DefaultSolidRegion() const { return *fDefaultSolidRegion; }
    auto& DefaultGaseousRegion() const { return *fDefaultGaseousRegion; }
    auto& ShieldRegion() const { return *fShieldRegion; }
    auto& SolenoidOrMagnetRegion() const { return *fSolenoidOrMagnetRegion; }
    auto& SpectrometerSensitiveRegion() const { return *fSpectrometerSensitiveRegion; }
    auto& TargetRegion() const { return *fTargetRegion; }
    auto& VacuumRegion() const { return *fVacuumRegion; }
    auto& MCPSensitiveRegion() const { return *fMCPSensitiveRegion; }

    auto& EMCSD() const { return *fEMCSD; }
    auto& CDCSD() const { return *fCDCSD; }
    auto& MCPSD() const { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::AcceleratorField,
                                        Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::EMC,
                                        Detector::Description::EMCField,
                                        Detector::Description::EMCShield,
                                        Detector::Description::MCP,
                                        Detector::Description::MultiplateCollimator,
                                        Detector::Description::Solenoid,
                                        Detector::Description::SpectrometerField,
                                        Detector::Description::SpectrometerMagnet,
                                        Detector::Description::SpectrometerShield,
                                        Detector::Description::Target,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Detector::Geometry::GeometryBase> fWorld;

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
