#pragma once

namespace MACE {

// FIXME: using inline namespace at this level (just under MACE) confuses VSCode's C++ extension.
// inline namespace Simulation {

namespace SimCalorimeter {}

namespace SimMACE {
    inline namespace Action {
        class ActionInitialization;
        class DetectorConstruction;
        class EventAction;
        class PrimaryGeneratorAction;
        class RunAction;
    }
    inline namespace Field {
        class AcceleratorField;
        class FirstBendField;
        class ParallelField;
        class SecondBendField;
        class SelectorField;
        class VerticalField;
    }
    inline namespace Hit {
        class CalorimeterHit;
        class VertexDetectorHit;
        class SpectrometerHit;
    }
    inline namespace Messenger {
        class AnalysisMessenger;
        class FieldMessenger;
        class PhysicsMessenger;
        class PrimaryGeneratorMessenger;
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
    inline namespace SD {
        class CalorimeterSD;
        class VertexDetectorSD;
        class SpectrometerSD;
    }
    inline namespace Utility {
        class Analysis;
        class Region;
    }
    class RunManager;
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

// } // inline namespace Simulation

}  // namespace MACE
