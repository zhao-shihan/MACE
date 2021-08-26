#pragma once

namespace MACE {
    namespace SimG4 {
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
            class Calorimeter; // ToDo
            class OrbitalDetector; // ToDo
            class Spectrometer; // ToDo
        }
        class DetectorConstruction;
        // physics
        namespace Physics {
            class AntiMuonium; // ToDo
            class Muonium;
            class MuoniumDecayChannel;
            class MuoniumPhysics;
            class MuoniumProduction;
            class PhysicsList;
        }
    }
    namespace SimMTransport {
        class Analysis;
        class Master;
        class MonteCarlo;
        struct Muonium;
        class RunManager;
        class Track;
        struct Vector3;
        class Worker;
    }
}