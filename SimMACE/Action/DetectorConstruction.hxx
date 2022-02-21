#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimMACE/Global.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/VertexDetectorShield.hxx"
#include "Geometry/Entity/Fast/World.hxx"

#define MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ClassName) \
    public: \
        [[nodiscard]] const std::shared_ptr<MACE::Geometry::Entity::Fast::ClassName>& Get##ClassName() const { return f##ClassName; } \
    private: \
        std::shared_ptr<MACE::Geometry::Entity::Fast::ClassName> f##ClassName = std::make_shared<MACE::Geometry::Entity::Fast::ClassName>()

class MACE::SimMACE::Action::DetectorConstruction final :
    public G4VUserDetectorConstruction {
public:
    DetectorConstruction(G4bool checkOverlaps);
    ~DetectorConstruction() noexcept = default;
    G4VPhysicalVolume* Construct() override;

private:
    void ConstructVolumes();
    void ConstructSD();
    void ConstructField();

    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Calorimeter);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(VertexDetector);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Collimator);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SelectorField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Target);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerCells);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerReadoutLayers);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(AcceleratorField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerBody);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(CalorimeterField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendSolenoid);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportSolenoid);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendSolenoid);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportSolenoid);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerShield);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportField);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportSolenoid);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(World);
    MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(VertexDetectorShield);

private:
    G4bool fCheckOverlaps;
};

#undef MACE_SIMMACE_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER
