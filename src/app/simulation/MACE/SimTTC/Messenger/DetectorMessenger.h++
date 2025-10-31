#pragma once

#include "MACE/SimTTC/Action/DetectorConstruction.h++"

#include "Mustard/Geant4X/Interface/DetectorMessenger.h++"

namespace MACE::SimTTC::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                           DetectorConstruction,
                                                                           "SimTTC"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() override = default;
};

} // namespace MACE::SimTTC::inline Messenger
