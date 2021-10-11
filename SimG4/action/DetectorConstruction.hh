#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4/Global.hh"
#include "SimG4/geometry/AcceleratorField.hh"
#include "SimG4/geometry/Calorimeter.hh"
#include "SimG4/geometry/Collimator.hh"
#include "SimG4/geometry/FirstBendField.hh"
#include "SimG4/geometry/FirstTransportField.hh"
#include "SimG4/geometry/OrbitalDetector.hh"
#include "SimG4/geometry/OrbitalDetectorShellField.hh"
#include "SimG4/geometry/OrbitalDetectorShield.hh"
#include "SimG4/geometry/SecondBendField.hh"
#include "SimG4/geometry/SecondTransportField.hh"
#include "SimG4/geometry/SelectorField.hh"
#include "SimG4/geometry/Spectrometer.hh"
#include "SimG4/geometry/SpectrometerField.hh"
#include "SimG4/geometry/SpectrometerGas.hh"
#include "SimG4/geometry/SpectrometerReadOutLayer.hh"
#include "SimG4/geometry/SpectrometerShield.hh"
#include "SimG4/geometry/Target.hh"
#include "SimG4/geometry/ThirdTransportField.hh"
#include "SimG4/geometry/World.hh"

#define MACE_SIMG4_DETECTOR_CONSTRUCTION_GEOMETRY_MEMBER(Name) \
    public: \
        const Geometry::Name* Name() const { return f##Name; } \
    private: \
        Geometry::Name* const f##Name = new Geometry::Name()

class MACE::SimG4::Action::DetectorConstruction : public G4VUserDetectorConstruction {
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