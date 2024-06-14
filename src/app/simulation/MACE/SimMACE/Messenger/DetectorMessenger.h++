#pragma once

#include "MACE/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"

namespace MACE::SimMACE::inline Messenger {

class DetectorMessenger final : public Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimMACE"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimMACE::inline Messenger
