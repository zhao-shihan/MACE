#pragma once

#include "Mustard/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"

namespace MACE::SimTarget::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimTarget"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimTarget::inline Messenger
