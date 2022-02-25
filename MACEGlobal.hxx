#pragma once

namespace MACE {

    namespace DataModel {
        inline namespace BranchSocket {
            template<typename Arith_t> class BasicBranchSocket;
            template<typename Class_t> class ClassBranchSocket;
        }
        inline namespace Hit {
            class CalorimeterHit;
            class VertexDetectorHit;
            class SpectrometerHit;
        }
        namespace Interface {
            template<typename Object_t, typename Address_t> class BranchSocket;
            class Data;
        }
        inline namespace RawHit { // no impl yet
            class CalorimeterRawHit;
            class VertexDetectorRawHit;
            class SpectrometerRawHit;
        }
        inline namespace SimHit {
            class CalorimeterSimHit;
            class VertexDetectorSimHit;
            class SpectrometerSimHit;
        }
        inline namespace SimRawHit { // no impl yet
            class CalorimeterSimRawHit;
            class VertexDetectorSimRawHit;
            class SpectrometerSimRawHit;
        }
        inline namespace Track {
            class HelixTrack;
            class PhysicsTrack;
        }
        class DataHub;
    }

    namespace Geometry {
        namespace Description {
            inline namespace DescendantsOfWorld {
                inline namespace DescendantsOfCalorimeterField {
                    class Calorimeter;
                    class VertexDetector;
                }
                inline namespace DescendantsOfFirstBendField {
                    class FirstBendSolenoid;
                }
                inline namespace DescendantsOfFirstTransportField {
                    class FirstTransportSolenoid;
                }
                inline namespace DescendantsOfSecondBendField {
                    class SecondBendSolenoid;
                }
                inline namespace DescendantsOfSecondTransportField {
                    class Collimator;
                    class SecondTransportSolenoid;
                    class SelectorField;
                }
                inline namespace DescendantsOfSpectrometerField {
                    inline namespace DescendantsOfAcceleratorField {
                        class Target;
                    }
                    inline namespace DescendantsOfSpectrometerBody {
                        inline namespace DescendantsOfSpectrometerReadoutLayer {
                            class SpectrometerCells;
                        }
                        class SpectrometerReadoutLayers;
                    }
                    class AcceleratorField;
                    class SpectrometerBody;
                }
                inline namespace DescendantsOfThirdTransportField {
                    class ThirdTransportSolenoid;
                }
                class CalorimeterField;
                class FirstBendField;
                class FirstTransportField;
                class SecondBendField;
                class SecondTransportField;
                class SpectrometerField;
                class SpectrometerShield;
                class ThirdTransportField;
                class VertexDetectorShield;
            }
            class World;
        }
        namespace Entity {
            namespace Fast {
                inline namespace DescendantsOfWorld {
                    inline namespace DescendantsOfCalorimeterField {
                        class Calorimeter;
                        class VertexDetector;
                    }
                    inline namespace DescendantsOfFirstBendField {
                        class FirstBendSolenoid;
                    }
                    inline namespace DescendantsOfFirstTransportField {
                        class FirstTransportSolenoid;
                    }
                    inline namespace DescendantsOfSecondBendField {
                        class SecondBendSolenoid;
                    }
                    inline namespace DescendantsOfSecondTransportField {
                        class Collimator;
                        class SecondTransportSolenoid;
                        class SelectorField;
                    }
                    inline namespace DescendantsOfSpectrometerField {
                        inline namespace DescendantsOfAcceleratorField {
                            class Target;
                        }
                        inline namespace DescendantsOfSpectrometerBody {
                            inline namespace DescendantsOfSpectrometerReadoutLayer {
                                class SpectrometerCells;
                            }
                            class SpectrometerReadoutLayers;
                        }
                        class AcceleratorField;
                        class SpectrometerBody;
                    }
                    inline namespace DescendantsOfThirdTransportField {
                        class ThirdTransportSolenoid;
                    }
                    class CalorimeterField;
                    class FirstBendField;
                    class FirstTransportField;
                    class SecondBendField;
                    class SecondTransportField;
                    class SpectrometerField;
                    class SpectrometerShield;
                    class ThirdTransportField;
                    class VertexDetectorShield;
                }
                class World;
            }
            namespace Full { // no impl yet
                class World;
            }
        }
        namespace Interface {
            class Description;
            class Entity;
        }
    }

    namespace ReconSpectrometer {
        namespace Fitter {
            template<class SpectromrterHit_t, class Track_t> class DirectSubSpaceLeastVariance;
            template<class SpectromrterHit_t, class Track_t> class Dummy;
        }
        namespace Interface {
            template<class SpectromrterHit_t, class Track_t> class Fitter;
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class Reconstructor;
        }
        namespace Reconstructor {
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class Hough;
            template<template<class H, class T> class FitterT_t, class SpectromrterHit_t, class Track_t> class TrueFinder;
        }
    }

    namespace SimCalorimeter {}

    namespace SimMACE {
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
        namespace Hit {
            class CalorimeterHit;
            class VertexDetectorHit;
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
            class VertexDetector;
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

    namespace SimSpectrometer {}

    inline namespace Utility {
        class FileTools4MPI;
    }

}
