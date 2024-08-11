#pragma once

#include "MACE/SimECal/Action/DetectorConstruction.h++"

#include "Mustard/Extension/Geant4X/Interface/DetectorMessenger.h++"

namespace MACE::SimECal::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                           DetectorConstruction,
                                                                           "SimECal"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace MACE::SimECal::inline Messenger
