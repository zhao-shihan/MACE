#pragma once

#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace MACE {
    // action

    // detector
    namespace Field {
        class AcceleratorField;
        class SpectrometerField;
    }
    namespace Geometry {
        class AcceleratorField;
        class Base;
        class Calorimeter;
        class Collimator;
        class OrbitalDetector;
        class OrbitalDetectorShellField;
        class ParallelTransportField;
        class SelectField;
        class Spectrometer;
        class SpectrometerField;
        class Target;
        class TurnField;
        class VerticalTransportField;
        class VolumeSet;
        class World;
    }
    namespace SD {
        class Calorimeter;
        class OrbitalDetector;
        class Spectrometer;
    }
    class DetectorConstruction;
}