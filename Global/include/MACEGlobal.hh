#pragma once

namespace MACE {
    namespace DataModel {
        namespace Base {
            namespace Persistency {
                class Container;
                class Handler;
                class Reader;
                class Writer;
            }
        }
        namespace Digitized {
            namespace Persistency {
                class Container;
                class Handler;
                class Reader;
                class Writer;
            }
            class CalorimeterHit;
            class OrbitalDetectorHit;
            class SpectrometerHit;
        }
        namespace Raw {
            namespace Persistency {
                class Container;
                class Handler;
                class Reader;
                class Writer;
            }
            class CalorimeterHit;
            class OrbitalDetectorHit;
            class SpectrometerHit;
        }
    }
    namespace Reconstruction {
        class ExperimentData;
        class Recognizer;
        class TOFAnalyzer;
    }
    namespace SimG4 {
        // action
        class ActionInitialization;
        class EventAction;
        class PrimaryGeneratorAction;
        class RunAction;
        // detector
        namespace Field {
            class AcceleratorField;
            class FirstBendField;
            class ParallelField;
            class SecondBendField;
            class SelectorField;
            class VerticalField;
        }
        namespace Geometry {
            class AcceleratorField;
            class BaseInterface;
            class Calorimeter;
            class Collimator;
            class FirstBendField;
            class FirstTransportField;
            class OrbitalDetector;
            class OrbitalDetectorShellField;
            class OrbitalDetectorShield;
            class SecondBendField;
            class SecondTransportField;
            class SelectorField;
            class Spectrometer;
            class SpectrometerField;
            class SpectrometerGas;
            class SpectrometerReadOutLayer;
            class SpectrometerShield;
            class Target;
            class ThirdTransportField;
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
}