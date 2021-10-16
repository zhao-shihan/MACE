#pragma once

namespace MACE {
    namespace DataModel {
        namespace Base {
            class Data;
            class PersistencyHandler;
        }
        namespace Hit {
            class CalorimeterHit;
            class OrbitalDetectorHit;
            class SpectrometerHit;
        }
        namespace RawHit {
            class CalorimeterRawHit;
            class OrbitalDetectorRawHit;
            class SpectrometerRawHit;
        }
        class PersistencyReader;
        class PersistencyWriter;
        class TreeNameHandler;
    }
    namespace Reconstruction {
        class ExperimentData;
        class Recognizer;
        class TOFAnalyzer;
    }
    namespace SimG4 {
        namespace Action {
            class ActionInitialization;
            class DetectorConstruction;
            class EventAction;
            class PrimaryGeneratorAction;
            class RunAction;
        }
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
        namespace Messenger {
            class AnalysisMessenger;
            class FieldMessenger;
            class MuonBeamMessenger;
            class PhysicsMessenger;
        }
        namespace Physics {
            class AntiMuonium;
            class AntiMuoniumDecayChannel;
            class Muonium;
            class MuoniumDecayChannel;
            class MuoniumPhysics;
            class MuoniumProduction;
            class MuoniumTransport;
            class PhysicsList;
        }
        namespace SD {
            class Calorimeter;
            class OrbitalDetector;
            class Spectrometer;
        }
        class Analysis;
    }
    namespace SimMTransport {
        class Analysis;
        class Global;
        class Master;
        class MonteCarlo;
        class RunManager;
        struct Step;
        class Track;
        class Worker;
    }
}