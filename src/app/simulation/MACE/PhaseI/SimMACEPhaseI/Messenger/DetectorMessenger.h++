#pragma once

#include "MACE/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger {

class DetectorMessenger final : public Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimMACEPhaseI"> {
    friend Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger
