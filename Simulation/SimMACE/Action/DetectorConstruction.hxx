#pragma once

#include <memory>

#include "G4VUserDetectorConstruction.hh"

#include "ObserverPtr.hxx"
#include "SimMACE/Global.hxx"

class MACE::SimMACE::DetectorConstruction final :
    public G4VUserDetectorConstruction {
    friend RunManager;

private:
    DetectorConstruction() = default;
    ~DetectorConstruction() noexcept = default;
    DetectorConstruction(const DetectorConstruction&) = delete;
    DetectorConstruction& operator=(const DetectorConstruction&) = delete;

public:
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

    std::shared_ptr<Geometry::Entity::Fast::Calorimeter> fCalorimeter;
    std::shared_ptr<Geometry::Entity::Fast::VertexDetector> fVertexDetector;
    std::shared_ptr<Geometry::Entity::Fast::FirstBendSolenoid> fFirstBendSolenoid;
    std::shared_ptr<Geometry::Entity::Fast::FirstTransportSolenoid> fFirstTransportSolenoid;
    std::shared_ptr<Geometry::Entity::Fast::SecondBendSolenoid> fSecondBendSolenoid;
    std::shared_ptr<Geometry::Entity::Fast::Collimator> fCollimator;
    std::shared_ptr<Geometry::Entity::Fast::SecondTransportSolenoid> fSecondTransportSolenoid;
    std::shared_ptr<Geometry::Entity::Fast::SelectorField> fSelectorField;
    std::shared_ptr<Geometry::Entity::Fast::Target> fTarget;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerSenseWires> fSpectrometerSenseWires;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerFieldWires> fSpectrometerFieldWires;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerSensitiveVolumes> fSpectrometerSensitiveVolumes;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerCells> fSpectrometerCells;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerReadoutLayers> fSpectrometerReadoutLayers;
    std::shared_ptr<Geometry::Entity::Fast::AcceleratorField> fAcceleratorField;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerBody> fSpectrometerBody;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerMagnet> fSpectrometerMagnet;
    std::shared_ptr<Geometry::Entity::Fast::ThirdTransportSolenoid> fThirdTransportSolenoid;
    std::shared_ptr<Geometry::Entity::Fast::CalorimeterField> fCalorimeterField;
    std::shared_ptr<Geometry::Entity::Fast::CalorimeterShield> fCalorimeterShield;
    std::shared_ptr<Geometry::Entity::Fast::FirstBendField> fFirstBendField;
    std::shared_ptr<Geometry::Entity::Fast::FirstTransportField> fFirstTransportField;
    std::shared_ptr<Geometry::Entity::Fast::SecondBendField> fSecondBendField;
    std::shared_ptr<Geometry::Entity::Fast::SecondTransportField> fSecondTransportField;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerField> fSpectrometerField;
    std::shared_ptr<Geometry::Entity::Fast::SpectrometerShield> fSpectrometerShield;
    std::shared_ptr<Geometry::Entity::Fast::ThirdTransportField> fThirdTransportField;
    std::shared_ptr<Geometry::Entity::Fast::World> fWorld;

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
