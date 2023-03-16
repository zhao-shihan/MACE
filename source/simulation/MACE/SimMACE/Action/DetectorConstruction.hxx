#pragma once

#include "MACE/Detector/Geometry/Fast/All.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4VUserDetectorConstruction.hh"

#include "gsl/gsl"

#include <memory>

namespace MACE::SimMACE {

namespace SD {

class CDCSD;
class EMCalSD;
class MCPSD;

} // namespace SD

namespace Action {

class DetectorConstruction final : public NonMoveableBase,
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

private:
    G4bool fCheckOverlap;

    gsl::not_null<std::shared_ptr<Detector::GeometryBase>> fWorld;

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

} // namespace Action

} // namespace MACE::SimMACE
