#pragma once

#include "MACE/Detector/Description/AcceleratorField.hxx"
#include "MACE/Detector/Description/BeamDegrader.hxx"
#include "MACE/Detector/Description/BeamMonitor.hxx"
#include "MACE/Detector/Description/CDC.hxx"
#include "MACE/Detector/Description/EMCal.hxx"
#include "MACE/Detector/Description/EMCalField.hxx"
#include "MACE/Detector/Description/EMCalShield.hxx"
#include "MACE/Detector/Description/MCP.hxx"
#include "MACE/Detector/Description/MultiplateCollimator.hxx"
#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/SpectrometerMagnet.hxx"
#include "MACE/Detector/Description/SpectrometerShield.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Detector/Description/World.hxx"
#include "MACE/Env/Memory/PassiveSingleton.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"

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

    auto& EMCalSensitiveRegion() const { return *fEMCalSensitiveRegion; }
    auto& DefaultSolidRegion() const { return *fDefaultSolidRegion; }
    auto& DefaultGaseousRegion() const { return *fDefaultGaseousRegion; }
    auto& ShieldRegion() const { return *fShieldRegion; }
    auto& SolenoidOrMagnetRegion() const { return *fSolenoidOrMagnetRegion; }
    auto& SpectrometerSensitiveRegion() const { return *fSpectrometerSensitiveRegion; }
    auto& TargetRegion() const { return *fTargetRegion; }
    auto& VacuumRegion() const { return *fVacuumRegion; }
    auto& MCPSensitiveRegion() const { return *fMCPSensitiveRegion; }

    auto& EMCalSD() const { return *fEMCalSD; }
    auto& CDCSD() const { return *fCDCSD; }
    auto& MCPSD() const { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::AcceleratorField,
                                        Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::EMCal,
                                        Detector::Description::EMCalField,
                                        Detector::Description::EMCalShield,
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
    Region* fEMCalSensitiveRegion;
    Region* fMCPSensitiveRegion;
    Region* fShieldRegion;
    Region* fSolenoidOrMagnetRegion;
    Region* fSpectrometerSensitiveRegion;
    Region* fTargetRegion;
    Region* fVacuumRegion;

    SD::CDCSD* fCDCSD;
    SD::EMCalSD* fEMCalSD;
    SD::MCPSD* fMCPSD;
};

} // namespace SimMACE::inline Action

} // namespace MACE
