#pragma once

namespace MACE {
    namespace SimG4 {
        // action
        class ActionInitialization;
        class EventAction;
        class PrimaryGeneratorAction;
        class RunAction;
        // detector
        namespace Field {
            class AcceleratorField;
            class CounterClockwiseGuideField;
            class ParallelTransportField;
            class SelectorField;
            class VerticalTransportField;
        }
        namespace Geometry {
            class AcceleratorField;
            class BaseInterface;
            class Calorimeter;
            class ClockwiseGuideField;
            class Collimator;
            class CounterClockwiseGuideField;
            class OrbitalDetector;
            class OrbitalDetectorShellField;
            class OrbitalDetectorShield;
            class ParallelTransportField;
            class SelectorField;
            class Spectrometer;
            class SpectrometerField;
            class SpectrometerReadOutLayer;
            class SpectrometerGas;
            class SpectrometerShield;
            class Target;
            class VerticalTransportField;
            class VolumeSet;
            class World;
        }
        namespace Hit {
            class CalorimeterHit;
            class OrbitalDetectorHit;
            class SpectrometerHit;
        }
        namespace SD {
            class Calorimeter;
            class OrbitalDetector;
            class Spectrometer;
        }
        class DetectorConstruction;
        // messenger
        class AnalysisMessenger;
        class FieldMessenger;
        class MuonBeamMessenger;
        class PhysicsMessenger;
        // physics
        namespace Physics {
            class AntiMuonium;
            class AntiMuoniumDecayChannel;
            class Muonium;
            class MuoniumDecayChannel;
            // class MuoniumLFV;
            class MuoniumPhysics;
            class MuoniumProduction;
            class MuoniumTransport;
            class PhysicsList;
        }
        class Analysis;
    }
    namespace SimMTransport {
        class Analysis;
        class Global;
        class Master;
        class MonteCarlo;
        struct Step;
        class RunManager;
        class Track;
        struct Vector3;
        class Worker;
    }
    namespace TrackReconstruction {
        class ExperimentData;
        class Hit;
        class Recognizer;
    }
}