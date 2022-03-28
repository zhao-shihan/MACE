#pragma once

#include "Core/Geometry/Entity/Fast/AcceleratorField.hxx"
#include "Core/Geometry/Entity/Fast/Calorimeter.hxx"
#include "Core/Geometry/Entity/Fast/CalorimeterField.hxx"
#include "Core/Geometry/Entity/Fast/CalorimeterShield.hxx"
#include "Core/Geometry/Entity/Fast/Collimator.hxx"
#include "Core/Geometry/Entity/Fast/FirstBendField.hxx"
#include "Core/Geometry/Entity/Fast/FirstBendSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/FirstTransportField.hxx"
#include "Core/Geometry/Entity/Fast/FirstTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SecondBendField.hxx"
#include "Core/Geometry/Entity/Fast/SecondBendSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SecondTransportField.hxx"
#include "Core/Geometry/Entity/Fast/SecondTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SelectorField.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerBody.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerCells.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerField.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerFieldWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerMagnet.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerReadoutLayers.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerSenseWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerSensitiveVolumes.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerShield.hxx"
#include "Core/Geometry/Entity/Fast/Target.hxx"
#include "Core/Geometry/Entity/Fast/ThirdTransportField.hxx"
#include "Core/Geometry/Entity/Fast/ThirdTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/VertexDetector.hxx"
#include "Core/Geometry/Entity/Fast/World.hxx"
#include "Utility/ObserverPtr.hxx"
#include "Simulation/SimMACE/Global.hxx"
#include "Simulation/SimMACE/SD/CalorimeterSD.hxx"
#include "Simulation/SimMACE/SD/SpectrometerSD.hxx"
#include "Simulation/SimMACE/SD/VertexDetectorSD.hxx"
#include "Simulation/SimMACE/Utility/Region.hxx"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

namespace MACE::Simulation::SimMACE::Action {

using namespace Geometry::Entity::Fast;
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

    [[nodiscard]] auto& GetCalorimeterSensitiveRegion() const { return *fCalorimeterSensitiveRegion; }
    [[nodiscard]] auto& GetDefaultSolidRegion() const { return *fDefaultSolidRegion; }
    [[nodiscard]] auto& GetDefaultGaseousRegion() const { return *fDefaultGaseousRegion; }
    [[nodiscard]] auto& GetShieldRegion() const { return *fShieldRegion; }
    [[nodiscard]] auto& GetSolenoidOrMagnetRegion() const { return *fSolenoidOrMagnetRegion; }
    [[nodiscard]] auto& GetSpectrometerSensitiveRegion() const { return *fSpectrometerSensitiveRegion; }
    [[nodiscard]] auto& GetTargetRegion() const { return *fTargetRegion; }
    [[nodiscard]] auto& GetVacuumRegion() const { return *fVacuumRegion; }
    [[nodiscard]] auto& GetVertexDetectorSensitiveRegion() const { return *fVertexDetectorSensitiveRegion; }

    [[nodiscard]] auto& GetCalorimeterSD() const { return *fCalorimeterSD; }
    [[nodiscard]] auto& GetSpectrometerSD() const { return *fSpectrometerSD; }
    [[nodiscard]] auto& GetVertexDetectorSD() const { return *fVertexDetectorSD; }

private:
    void ConstructVolumes();
    void ConstructRegions();
    void ConstructSDs();
    void ConstructFields();

private:
    G4bool fCheckOverlaps = false;

    std::shared_ptr<Calorimeter> fCalorimeter;
    std::shared_ptr<VertexDetector> fVertexDetector;
    std::shared_ptr<FirstBendSolenoid> fFirstBendSolenoid;
    std::shared_ptr<FirstTransportSolenoid> fFirstTransportSolenoid;
    std::shared_ptr<SecondBendSolenoid> fSecondBendSolenoid;
    std::shared_ptr<Collimator> fCollimator;
    std::shared_ptr<SecondTransportSolenoid> fSecondTransportSolenoid;
    std::shared_ptr<SelectorField> fSelectorField;
    std::shared_ptr<Target> fTarget;
    std::shared_ptr<SpectrometerSenseWires> fSpectrometerSenseWires;
    std::shared_ptr<SpectrometerFieldWires> fSpectrometerFieldWires;
    std::shared_ptr<SpectrometerSensitiveVolumes> fSpectrometerSensitiveVolumes;
    std::shared_ptr<SpectrometerCells> fSpectrometerCells;
    std::shared_ptr<SpectrometerReadoutLayers> fSpectrometerReadoutLayers;
    std::shared_ptr<AcceleratorField> fAcceleratorField;
    std::shared_ptr<SpectrometerBody> fSpectrometerBody;
    std::shared_ptr<SpectrometerMagnet> fSpectrometerMagnet;
    std::shared_ptr<ThirdTransportSolenoid> fThirdTransportSolenoid;
    std::shared_ptr<CalorimeterField> fCalorimeterField;
    std::shared_ptr<CalorimeterShield> fCalorimeterShield;
    std::shared_ptr<FirstBendField> fFirstBendField;
    std::shared_ptr<FirstTransportField> fFirstTransportField;
    std::shared_ptr<SecondBendField> fSecondBendField;
    std::shared_ptr<SecondTransportField> fSecondTransportField;
    std::shared_ptr<SpectrometerField> fSpectrometerField;
    std::shared_ptr<SpectrometerShield> fSpectrometerShield;
    std::shared_ptr<ThirdTransportField> fThirdTransportField;
    std::shared_ptr<World> fWorld;

    ObserverPtr<Region> fCalorimeterSensitiveRegion;
    ObserverPtr<Region> fDefaultSolidRegion;
    ObserverPtr<Region> fDefaultGaseousRegion;
    ObserverPtr<Region> fShieldRegion;
    ObserverPtr<Region> fSolenoidOrMagnetRegion;
    ObserverPtr<Region> fSpectrometerSensitiveRegion;
    ObserverPtr<Region> fTargetRegion;
    ObserverPtr<Region> fVacuumRegion;
    ObserverPtr<Region> fVertexDetectorSensitiveRegion;

    ObserverPtr<CalorimeterSD> fCalorimeterSD;
    ObserverPtr<SpectrometerSD> fSpectrometerSD;
    ObserverPtr<VertexDetectorSD> fVertexDetectorSD;
};

} // namespace MACE::Simulation::SimMACE::Action
