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
        class MuonBeamMessenger;
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