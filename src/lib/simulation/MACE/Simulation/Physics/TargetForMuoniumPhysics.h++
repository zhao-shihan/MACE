#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

#include "G4ThreeVector.hh"

#include <concepts>

namespace MACE::inline Simulation::Physics {

template<typename T>
concept TargetForMuoniumPhysics =
    requires(T target, G4ThreeVector x) {
        requires Detector::Description::Description<T>;
        { target.VolumeContain(x) } -> std::convertible_to<bool>;
        { target.Contain(x) } -> std::convertible_to<bool>;
    };

} // namespace MACE::inline Simulation::Physics
