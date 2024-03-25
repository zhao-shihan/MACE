#pragma once

#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/Simulation/Messenger/DetectorMessenger.h++"

namespace MACE::SimMACE::inline Messenger {

class DetectorMessenger final : public Simulation::DetectorMessenger<DetectorMessenger,
                                                                     DetectorConstruction,
                                                                     "SimMACE"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimMACE::inline Messenger
