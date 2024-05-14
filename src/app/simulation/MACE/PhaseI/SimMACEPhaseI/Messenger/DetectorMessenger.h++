#pragma once

#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"
#include "MACE/Simulation/Messenger/DetectorMessenger.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger {

class DetectorMessenger final : public Simulation::DetectorMessenger<DetectorMessenger,
                                                                     DetectorConstruction,
                                                                     "SimMACEPhaseI"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger
