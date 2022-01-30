#pragma once

namespace MACE {

    namespace DataModel {
        namespace Interface {
            class Data;
            class PersistencyHandler;
        }
        inline namespace Hit {
            class CalorimeterHit;
            class OrbitalDetectorHit;
            class SpectrometerHit;
        }
        inline namespace RawHit { // no impl yet
            class CalorimeterRawHit;
            class OrbitalDetectorRawHit;
            class SpectrometerRawHit;
        }
        template<typename Value_t> struct Column;
        class PersistencyReader;
        class PersistencyWriter;
    }

    namespace Geometry {
        namespace Description {
            inline namespace DescendantsOfWorld {
                inline namespace DescendantsOfCalorimeterField {
                    class Calorimeter;
                    class OrbitalDetector;
                }
                inline namespace DescendantsOfSecondTransportField {
                    class Collimator;
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
                        class SpectrometerReadoutLayer;
                    }
                    class AcceleratorField;
                    class SpectrometerBody;
                }
                class CalorimeterField;
                class FirstBendField;
                class FirstBendSolenoid;
                class FirstTransportField;
                class FirstTransportSolenoid;
                class OrbitalDetectorShield;
                class SecondBendField;
                class SecondBendSolenoid;
                class SecondTransportField;
                class SecondTransportSolenoid;
                class SpectrometerField;
                class SpectrometerShield;
                class ThirdTransportField;
                class ThirdTransportSolenoid;
            }
            class World;
        }
        namespace Entity {
            namespace Fast {
                inline namespace DescendantsOfWorld {
                    inline namespace DescendantsOfCalorimeterField {
                        class Calorimeter;
                        class OrbitalDetector;
                    }
                    inline namespace DescendantsOfSecondTransportField {
                        class Collimator;
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
                            class SpectrometerReadoutLayer;
                        }
                        class AcceleratorField;
                        class SpectrometerBody;
                    }
                    class CalorimeterField;
                    class FirstBendField;
                    class FirstBendSolenoid;
                    class FirstTransportField;
                    class FirstTransportSolenoid;
                    class OrbitalDetectorShield;
                    class SecondBendField;
                    class SecondBendSolenoid;
                    class SecondTransportField;
                    class SecondTransportSolenoid;
                    class SpectrometerField;
                    class SpectrometerShield;
                    class ThirdTransportField;
                    class ThirdTransportSolenoid;
                }
                class World;
            }
            namespace Full { // no impl yet
                class World;
            }
        }
        namespace Interface {
            class Description;
            template<class Volume_t> class Entity;
            template<class Volume_t, class... RequiredDescriptions> class EntityWithDescription;
            template<class... RequiredDescriptions> class EntityG4;
            template<class... RequiredDescriptions> class EntityROOT; // DO NOT USE for now.
        }
    }

    namespace ReconSpectrometer {
        namespace Fitter {
            template<class SpectromrterHit_t> class DirectLeastChiSquare;
        }
        namespace Interface {
            template<class SpectromrterHit_t> class Fitter;
            template<template<class T> class FitterT_t, class SpectromrterHit_t> class Reconstructor;
        }
        namespace Reconstructor {
            template<template<class T> class FitterT_t, class SpectromrterHit_t> class Hough;
        }
        struct HelixParameters;
    }

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