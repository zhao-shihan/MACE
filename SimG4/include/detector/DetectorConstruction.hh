#pragma once

#include "G4VUserDetectorConstruction.hh"

#include "SimG4Global.hh"

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

    Geometry::AcceleratorField* const           fAcceleratorField;
    Geometry::Calorimeter* const                fCalorimeter;
    Geometry::Collimator* const                 fCollimator;
    Geometry::OrbitalDetector* const            fOrbitalDetector;
    Geometry::OrbitalDetectorShellField* const  fOrbitalDetectorShellField;
    Geometry::OrbitalDetectorShield* const      fOrbitalDetectorShield;
    Geometry::ParallelTransportField* const     fParallelTransportField;
    Geometry::SelectorField* const              fSelectorField;
    Geometry::Spectrometer* const               fSpectormeter;
    Geometry::SpectrometerField* const          fSpectormeterField;
    Geometry::SpectrometerReadOutLayer* const   fSpectrometerReadOutLayer;
    Geometry::SpectrometerShield* const         fSpectrometerShield;
    Geometry::Target* const                     fTarget;
    Geometry::CounterClockwiseGuideField* const fCounterClockwiseGuideField;
    Geometry::VerticalTransportField* const     fVerticalTransportField;
    Geometry::World* const                      fWorld;
};
