#pragma once

#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/Simulation/Messenger/DetectorMessenger.h++"

namespace MACE::SimTarget::inline Messenger {

class DetectorMessenger final : public Simulation::DetectorMessenger<DetectorMessenger,
                                                                     DetectorConstruction,
                                                                     "SimTarget"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimTarget::inline Messenger
