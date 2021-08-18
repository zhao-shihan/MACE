#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "MACEGlobal.hh"

class MACE::DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

private:
    void ConstructGeometry();
    void ConstructField();
    // void ConstructSD();

    MACE::Geometry::AcceleratorField* const          fAcceleratorField;
    MACE::Geometry::Calorimeter* const               fCalorimeter;
    MACE::Geometry::Collimator* const                fCollimator;
    MACE::Geometry::OrbitalDetector* const           fOrbitalDetector;
    MACE::Geometry::OrbitalDetectorShellField* const fOrbitalDetectorShellField;
    MACE::Geometry::OrbitalDetectorShield* const     fOrbitalDetectorShield;
    MACE::Geometry::ParallelTransportField* const    fParallelTransportField;
    MACE::Geometry::SelectField* const               fSelectField;
    MACE::Geometry::Spectrometer* const              fSpectormeter;
    MACE::Geometry::SpectrometerField* const         fSpectormeterField;
    MACE::Geometry::SpectrometerShield* const        fSpectrometerShield;
    MACE::Geometry::Target* const                    fTarget;
    MACE::Geometry::TurnField* const                 fTurnField;
    MACE::Geometry::VerticalTransportField* const    fVerticalTransportField;
    MACE::Geometry::World* const                     fWorld;
};
