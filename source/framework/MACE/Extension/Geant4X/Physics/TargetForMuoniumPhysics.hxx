#pragma once

#include "MACE/Detector/Description/DescriptionBase.hxx"

#include "G4ThreeVector.hh"

#include <concepts>

namespace MACE::inline Extension::Geant4X::Physics {

template<class T>
concept TargetForMuoniumPhysics =
    requires(T target, G4ThreeVector x) {
        requires Detector::Description::Description<T>;
        { target.VolumeContain(x) } -> std::convertible_to<bool>;
        { target.Contain(x) } -> std::convertible_to<bool>;
    };

} // namespace MACE::inline Extension::Geant4X::Physics
