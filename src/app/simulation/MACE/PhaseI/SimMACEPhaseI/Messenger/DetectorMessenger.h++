#pragma once

#include "Mustard/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"

namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimMACEPhaseI"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger
