#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4/Global.hh"
#include "SimG4/Geometry/AcceleratorField.hh"
#include "SimG4/Geometry/Calorimeter.hh"
#include "SimG4/Geometry/Collimator.hh"
#include "SimG4/Geometry/FirstBendField.hh"
#include "SimG4/Geometry/FirstTransportField.hh"
#include "SimG4/Geometry/OrbitalDetector.hh"
#include "SimG4/Geometry/OrbitalDetectorShellField.hh"
#include "SimG4/Geometry/OrbitalDetectorShield.hh"
#include "SimG4/Geometry/SecondBendField.hh"
#include "SimG4/Geometry/SecondTransportField.hh"
#include "SimG4/Geometry/SelectorField.hh"
#include "SimG4/Geometry/Spectrometer.hh"
#include "SimG4/Geometry/SpectrometerField.hh"
#include "SimG4/Geometry/SpectrometerGas.hh"
#include "SimG4/Geometry/SpectrometerReadOutLayer.hh"
#include "SimG4/Geometry/SpectrometerShield.hh"
#include "SimG4/Geometry/Target.hh"
#include "SimG4/Geometry/ThirdTransportField.hh"
#include "SimG4/Geometry/World.hh"

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