#pragma once

#include "Mustard/Extension/Geant4X/Interface/DetectorMessenger.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"

namespace MACE::SimEMC::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                  DetectorConstruction,
                                                                  "SimEMC"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimEMC::inline Messenger
