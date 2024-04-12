#pragma once

#include "MACE/SimMMS/Action/DetectorConstruction.h++"
#include "MACE/Simulation/Messenger/DetectorMessenger.h++"

namespace MACE::SimMMS::inline Messenger {

class DetectorMessenger final : public Simulation::DetectorMessenger<DetectorMessenger,
                                                                     DetectorConstruction,
                                                                     "SimMMS"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimMMS::inline Messenger
