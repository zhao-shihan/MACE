#pragma once

#include "MACE/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/SimMMS/Action/DetectorConstruction.h++"

namespace MACE::SimMMS::inline Messenger {

class DetectorMessenger final : public Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimMMS"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimMMS::inline Messenger
