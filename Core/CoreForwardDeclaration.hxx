#pragma once

#include "CoreConcepts.hxx"

namespace MACE {

    // FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension.
    // inline namespace Core {

    namespace DataModel {
        inline namespace BranchSocket {
            template<ClassType Class_t> class ClassBranchSocket;
            template<FundamentalType Fund_t> class FundamentalBranchSocket;
            class ShortStringBranchSocket;
            template<FundamentalType Fund_t> class Vector2BranchSocket;
            template<FundamentalType Fund_t> class Vector3BranchSocket;
            template<FundamentalType Fund_t, int Size> class VectorBranchSocket;
        }
        inline namespace Hit {
            class CalorimeterHit;
            class VertexDetectorHit;
            class SpectrometerHit;
        }
        namespace Interface {
            template<typename Type, bool UseReferenceInGetAndSet> class BranchSocket;
            class Transient;
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
        inline namespace Vertex {
            class MuoniumVertex;
        }
        class DataHub;
    } // inline namespace DataModel

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
                        inline namespace DescendantsOfSpectrometerReadoutLayers {
                            inline namespace DescendantsOfSpectrometerCells {
                                inline namespace DescendantsOfSpectrometerSensitiveVolumes {
                                    class SpectrometerSenseWires;
                                }
                                class SpectrometerFieldWires;
                                class SpectrometerSensitiveVolumes;
                            }
                            class SpectrometerCells;
                        }
                        class SpectrometerReadoutLayers;
                    }
                    class AcceleratorField;
                    class SpectrometerBody;
                    class SpectrometerMagnet;
                }
                inline namespace DescendantsOfThirdTransportField {
                    class ThirdTransportSolenoid;
                }
                class CalorimeterField;
                class CalorimeterShield;
                class FirstBendField;
                class FirstTransportField;
                class SecondBendField;
                class SecondTransportField;
                class SpectrometerField;
                class SpectrometerShield;
                class ThirdTransportField;
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
                            inline namespace DescendantsOfSpectrometerReadoutLayers {
                                inline namespace DescendantsOfSpectrometerCells {
                                    inline namespace DescendantsOfSpectrometerSensitiveVolumes {
                                        class SpectrometerSenseWires;
                                    }
                                    class SpectrometerFieldWires;
                                    class SpectrometerSensitiveVolumes;
                                }
                                class SpectrometerCells;
                            }
                            class SpectrometerReadoutLayers;
                        }
                        class AcceleratorField;
                        class SpectrometerBody;
                        class SpectrometerMagnet;
                    }
                    inline namespace DescendantsOfThirdTransportField {
                        class ThirdTransportSolenoid;
                    }
                    class CalorimeterField;
                    class CalorimeterShield;
                    class FirstBendField;
                    class FirstTransportField;
                    class SecondBendField;
                    class SecondTransportField;
                    class SpectrometerField;
                    class SpectrometerShield;
                    class ThirdTransportField;
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
    } // namespace Geometry

    // } // inline namespace Core

} // namespace MACE
