#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4Global.hh"
#include "detector/geometry/AcceleratorField.hh"
#include "detector/geometry/Calorimeter.hh"
#include "detector/geometry/Collimator.hh"
#include "detector/geometry/FirstBendField.hh"
#include "detector/geometry/FirstTransportField.hh"
#include "detector/geometry/OrbitalDetector.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"
#include "detector/geometry/OrbitalDetectorShield.hh"
#include "detector/geometry/SecondBendField.hh"
#include "detector/geometry/SecondTransportField.hh"
#include "detector/geometry/SelectorField.hh"
#include "detector/geometry/Spectrometer.hh"
#include "detector/geometry/SpectrometerField.hh"
#include "detector/geometry/SpectrometerGas.hh"
#include "detector/geometry/SpectrometerReadOutLayer.hh"
#include "detector/geometry/SpectrometerShield.hh"
#include "detector/geometry/Target.hh"
#include "detector/geometry/ThirdTransportField.hh"
#include "detector/geometry/World.hh"

#define MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Name) \
    public: \
        const Geometry::Name* Name() const { return f##Name; } \
    private: \
        Geometry::Name* const f##Name = new Geometry::Name()

class MACE::SimG4::DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction();
    G4VPhysicalVolume* Construct() override;

    auto* GetTarget() const { return fTarget; }

private:
    void ConstructGeometry();
    void ConstructSD();
    void ConstructField();

    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(AcceleratorField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Calorimeter);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Collimator);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(FirstTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetector);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetectorShellField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(OrbitalDetectorShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondBendField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SecondTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SelectorField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Spectrometer);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerGas);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerReadOutLayer);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(SpectrometerShield);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Target);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(ThirdTransportField);
    MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(World);
};

#undef MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER