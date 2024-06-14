#pragma once

#include "MACE/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"

namespace MACE::SimTarget::inline Messenger {

class DetectorMessenger final : public Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimTarget"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimTarget::inline Messenger
