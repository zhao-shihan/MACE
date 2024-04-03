#pragma once

#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/Simulation/Messenger/DetectorMessenger.h++"

namespace MACE::SimEMC::inline Messenger {

class DetectorMessenger final : public Simulation::DetectorMessenger<DetectorMessenger,
                                                                     DetectorConstruction,
                                                                     "SimEMC"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimEMC::inline Messenger
