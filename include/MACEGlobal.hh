#pragma once

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

namespace MACE {
    // action
    class ActionInitialization;
    class PrimaryGeneratorAction;

    // detector
    namespace Field {
        class AcceleratorField;
        class SelectField;
        class TurnField;
    }
    namespace Geometry {
        class AcceleratorField;
        class BaseInterface;
        class Calorimeter;
        class Collimator;
        class OrbitalDetector;
        class OrbitalDetectorShellField;
        class OrbitalDetectorShield;
        class ParallelTransportField;
        class SelectField;
        class Spectrometer;
        class SpectrometerField;
        class SpectrometerShield;
        class Target;
        class TurnField;
        class VerticalTransportField;
        class VolumeSet;
        class World;
    }
    namespace SD {
        class Calorimeter;//
        class OrbitalDetector;//
        class Spectrometer;//
    }
    class DetectorConstruction;
}