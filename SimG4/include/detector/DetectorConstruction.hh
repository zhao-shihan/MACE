#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4Global.hh"

class MACE::SimG4::DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    auto* GetTarget() const { return fTarget; }

private:
    void ConstructGeometry();
    void ConstructField();
    // void ConstructSD();

    MACE::SimG4::Geometry::AcceleratorField* const          fAcceleratorField;
    MACE::SimG4::Geometry::Calorimeter* const               fCalorimeter;
    MACE::SimG4::Geometry::Collimator* const                fCollimator;
    MACE::SimG4::Geometry::OrbitalDetector* const           fOrbitalDetector;
    MACE::SimG4::Geometry::OrbitalDetectorShellField* const fOrbitalDetectorShellField;
    MACE::SimG4::Geometry::OrbitalDetectorShield* const     fOrbitalDetectorShield;
    MACE::SimG4::Geometry::ParallelTransportField* const    fParallelTransportField;
    MACE::SimG4::Geometry::SelectField* const               fSelectField;
    MACE::SimG4::Geometry::Spectrometer* const              fSpectormeter;
    MACE::SimG4::Geometry::SpectrometerField* const         fSpectormeterField;
    MACE::SimG4::Geometry::SpectrometerShield* const        fSpectrometerShield;
    MACE::SimG4::Geometry::Target* const                    fTarget;
    MACE::SimG4::Geometry::TurnField* const                 fTurnField;
    MACE::SimG4::Geometry::VerticalTransportField* const    fVerticalTransportField;
    MACE::SimG4::Geometry::World* const                     fWorld;
};
