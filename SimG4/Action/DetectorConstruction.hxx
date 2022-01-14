#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4/Global.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/OrbitalDetector.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayer.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/OrbitalDetectorShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/World.hxx"

#define MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ClassName) \
    public: \
        const MACE::Geometry::Entity::Fast::ClassName* Get##ClassName() const { return f##ClassName; } \
    private: \
        MACE::Geometry::Entity::Fast::ClassName* const f##ClassName = new MACE::Geometry::Entity::Fast::ClassName()

class MACE::SimG4::Action::DetectorConstruction :
    public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction();
    G4VPhysicalVolume* Construct() override;

private:
    void ConstructVolumes();
    void ConstructSD();
    void ConstructField();

    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Calorimeter);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetector);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Collimator);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SelectorField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Target);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerCells);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerReadoutLayer);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(AcceleratorField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerBody);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(CalorimeterField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendSolenoid);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportSolenoid);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetectorShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendSolenoid);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportSolenoid);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportSolenoid);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(World);
};

#undef MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER