#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"

#include "G4VUserDetectorConstruction.hh"

#include "gsl/gsl"

#include <memory>

namespace MACE {

namespace Detector {

namespace Description {

class BeamDegrader;
class BeamMonitor;
class CDC;
class Collimator;
class EMCal;
class EMCalField;
class EMCalShield;
class AcceleratorField;
class MCP;
class SelectorField;
class SpectrometerField;
class SpectrometerMagnet;
class SpectrometerShield;
class Target;
class Solenoid;
class World;

} // namespace Description

namespace Geometry {

class GeometryBase;

} // namespace Geometry

} // namespace Detector

namespace SimMACE::inline Action {

class DetectorConstruction final : public Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlap = checkOverlaps; }

    auto& GetEMCalSensitiveRegion() const { return *fEMCalSensitiveRegion; }
    auto& GetDefaultSolidRegion() const { return *fDefaultSolidRegion; }
    auto& GetDefaultGaseousRegion() const { return *fDefaultGaseousRegion; }
    auto& GetShieldRegion() const { return *fShieldRegion; }
    auto& GetSolenoidOrMagnetRegion() const { return *fSolenoidOrMagnetRegion; }
    auto& GetSpectrometerSensitiveRegion() const { return *fSpectrometerSensitiveRegion; }
    auto& GetTargetRegion() const { return *fTargetRegion; }
    auto& GetVacuumRegion() const { return *fVacuumRegion; }
    auto& GetMCPSensitiveRegion() const { return *fMCPSensitiveRegion; }

    auto& GetEMCalSD() const { return *fEMCalSD; }
    auto& GetCDCSD() const { return *fCDCSD; }
    auto& GetMCPSD() const { return *fMCPSD; }

public:
    using DescriptionInUse = std::tuple<Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::Collimator,
                                        Detector::Description::EMCal,
                                        Detector::Description::EMCalField,
                                        Detector::Description::EMCalShield,
                                        Detector::Description::AcceleratorField,
                                        Detector::Description::MCP,
                                        Detector::Description::SelectorField,
                                        Detector::Description::SpectrometerField,
                                        Detector::Description::SpectrometerMagnet,
                                        Detector::Description::SpectrometerShield,
                                        Detector::Description::Target,
                                        Detector::Description::Solenoid,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    gsl::not_null<std::shared_ptr<Detector::Geometry::GeometryBase>> fWorld;

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

    CDCSD* fCDCSD;
    EMCalSD* fEMCalSD;
    MCPSD* fMCPSD;
};

} // namespace SimMACE::inline Action

} // namespace MACE
