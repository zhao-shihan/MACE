#pragma once

#include "MACE/Core/Geometry/Entity/Fast/All.hxx"
#include "MACE/Simulation/SimMACE/SD/CDCSD.hxx"
#include "MACE/Simulation/SimMACE/SD/EMCalSD.hxx"
#include "MACE/Simulation/SimMACE/SD/MCPSD.hxx"
#include "MACE/Simulation/SimMACE/Utility/Region.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE::Simulation::SimMACE::Action {

using namespace Core::Geometry::Entity::Fast;
using namespace SD;
using MACE::Utility::ObserverPtr;
using Utility::Region;

class DetectorConstruction final : public G4VUserDetectorConstruction {
public:
    DetectorConstruction() = default;
    ~DetectorConstruction() noexcept = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

    G4VPhysicalVolume* Construct() override;

    void SetCheckOverlaps(G4bool checkOverlaps) { fCheckOverlaps = checkOverlaps; }

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
    G4bool fCheckOverlaps = false;

    std::shared_ptr<CDCBody> fCDCBody;
    std::shared_ptr<CDCCell> fCDCCell;
    std::shared_ptr<CDCFieldWire> fCDCFieldWire;
    std::shared_ptr<CDCLayer> fCDCLayer;
    std::shared_ptr<CDCSenseWire> fCDCSenseWire;
    std::shared_ptr<CDCSensitiveVolume> fCDCSensitiveVolume;
    std::shared_ptr<Collimator> fCollimator;
    std::shared_ptr<EMCal> fEMCal;
    std::shared_ptr<EMCalField> fEMCalField;
    std::shared_ptr<EMCalShield> fEMCalShield;
    std::shared_ptr<FirstBendField> fFirstBendField;
    std::shared_ptr<FirstBendSolenoid> fFirstBendSolenoid;
    std::shared_ptr<FirstTransportField> fFirstTransportField;
    std::shared_ptr<FirstTransportSolenoid> fFirstTransportSolenoid;
    std::shared_ptr<LinacField> fLinacField;
    std::shared_ptr<MCP> fMCP;
    std::shared_ptr<SecondBendField> fSecondBendField;
    std::shared_ptr<SecondBendSolenoid> fSecondBendSolenoid;
    std::shared_ptr<SecondTransportField> fSecondTransportField;
    std::shared_ptr<SecondTransportSolenoid> fSecondTransportSolenoid;
    std::shared_ptr<SelectorField> fSelectorField;
    std::shared_ptr<SpectrometerField> fSpectrometerField;
    std::shared_ptr<SpectrometerMagnet> fSpectrometerMagnet;
    std::shared_ptr<SpectrometerShield> fSpectrometerShield;
    std::shared_ptr<Target> fTarget;
    std::shared_ptr<ThirdTransportField> fThirdTransportField;
    std::shared_ptr<ThirdTransportSolenoid> fThirdTransportSolenoid;
    std::shared_ptr<World> fWorld;

    ObserverPtr<Region> fEMCalSensitiveRegion;
    ObserverPtr<Region> fDefaultSolidRegion;
    ObserverPtr<Region> fDefaultGaseousRegion;
    ObserverPtr<Region> fShieldRegion;
    ObserverPtr<Region> fSolenoidOrMagnetRegion;
    ObserverPtr<Region> fSpectrometerSensitiveRegion;
    ObserverPtr<Region> fTargetRegion;
    ObserverPtr<Region> fVacuumRegion;
    ObserverPtr<Region> fMCPSensitiveRegion;

    ObserverPtr<CDCSD> fCDCSD;
    ObserverPtr<EMCalSD> fEMCalSD;
    ObserverPtr<MCPSD> fMCPSD;
};

} // namespace MACE::Simulation::SimMACE::Action
