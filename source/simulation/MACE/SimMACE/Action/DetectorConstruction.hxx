#pragma once

#include "MACE/Core/Geometry/Entity/Fast/All.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE::SimMACE {

namespace SD {

class CDCSD;
class EMCalSD;
class MCPSD;

} // namespace SD

namespace Action {

using MACE::Utility::ObserverPtr;

class DetectorConstruction final : public Utility::NonCopyableBase,
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
    void ConstructVolumes();
    void ConstructMaterials();
    void ConstructRegions();
    void ConstructSDs();
    void ConstructFields();

private:
    G4bool fCheckOverlap;

    std::shared_ptr<Core::Geometry::IEntity> fBeamDegrader;
    std::shared_ptr<Core::Geometry::IEntity> fBeamMonitor;
    std::shared_ptr<Core::Geometry::IEntity> fCDCBody;
    std::shared_ptr<Core::Geometry::IEntity> fCDCCell;
    std::shared_ptr<Core::Geometry::IEntity> fCDCFieldWire;
    std::shared_ptr<Core::Geometry::IEntity> fCDCLayer;
    std::shared_ptr<Core::Geometry::IEntity> fCDCSenseWire;
    std::shared_ptr<Core::Geometry::IEntity> fCDCSensitiveVolume;
    std::shared_ptr<Core::Geometry::IEntity> fCollimator;
    std::shared_ptr<Core::Geometry::IEntity> fEMCal;
    std::shared_ptr<Core::Geometry::IEntity> fEMCalField;
    std::shared_ptr<Core::Geometry::IEntity> fEMCalShield;
    std::shared_ptr<Core::Geometry::IEntity> fFirstBendField;
    std::shared_ptr<Core::Geometry::IEntity> fFirstBendSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fFirstTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fFirstTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fLinacField;
    std::shared_ptr<Core::Geometry::IEntity> fMCP;
    std::shared_ptr<Core::Geometry::IEntity> fSecondBendField;
    std::shared_ptr<Core::Geometry::IEntity> fSecondBendSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fSecondTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fSecondTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fSelectorField;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerField;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerMagnet;
    std::shared_ptr<Core::Geometry::IEntity> fSpectrometerShield;
    std::shared_ptr<Core::Geometry::IEntity> fTarget;
    std::shared_ptr<Core::Geometry::IEntity> fThirdTransportField;
    std::shared_ptr<Core::Geometry::IEntity> fThirdTransportSolenoid;
    std::shared_ptr<Core::Geometry::IEntity> fWorld;

    ObserverPtr<Region> fEMCalSensitiveRegion;
    ObserverPtr<Region> fDefaultSolidRegion;
    ObserverPtr<Region> fDefaultGaseousRegion;
    ObserverPtr<Region> fShieldRegion;
    ObserverPtr<Region> fSolenoidOrMagnetRegion;
    ObserverPtr<Region> fSpectrometerSensitiveRegion;
    ObserverPtr<Region> fTargetRegion;
    ObserverPtr<Region> fVacuumRegion;
    ObserverPtr<Region> fMCPSensitiveRegion;

    ObserverPtr<SD::CDCSD> fCDCSD;
    ObserverPtr<SD::EMCalSD> fEMCalSD;
    ObserverPtr<SD::MCPSD> fMCPSD;
};

} // namespace Action

} // namespace MACE::SimMACE
