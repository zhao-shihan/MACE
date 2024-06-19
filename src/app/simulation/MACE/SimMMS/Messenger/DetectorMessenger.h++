#pragma once

#include "MACE/SimMMS/Action/DetectorConstruction.h++"

#include "Mustard/Extension/Geant4X/Interface/DetectorMessenger.h++"

namespace MACE::SimMMS::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                           DetectorConstruction,
                                                                           "SimMMS"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimMMS::inline Messenger
