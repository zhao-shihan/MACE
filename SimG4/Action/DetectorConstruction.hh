#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4/Global.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/OrbitalDetector.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerCells.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerShell.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/OrbitalDetectorShield.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportField.hh"
#include "Geometry/Entity/Fast/World.hh"

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
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(AcceleratorField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerCells);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerShell);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(CalorimeterField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetectorShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(World);
};

#undef MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER