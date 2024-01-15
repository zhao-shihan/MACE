#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F>
concept ElectromagneticField =
    requires(const F f, stdx::array3d x) {
        { f.BFieldAt(x) } -> std::same_as<stdx::array3d>;
        { f.EFieldAt(x) } -> std::same_as<stdx::array3d>;
        { f.BEFieldAt(x).B } -> std::same_as<stdx::array3d&&>;
        { f.BEFieldAt(x).E } -> std::same_as<stdx::array3d&&>;
        { f.template BFieldAt<stdx::array3d>({}) } -> std::same_as<stdx::array3d>;
        { f.template EFieldAt<stdx::array3d>({}) } -> std::same_as<stdx::array3d>;
        { f.template BEFieldAt<stdx::array3d>({}).B } -> std::same_as<stdx::array3d&&>;
        { f.template BEFieldAt<stdx::array3d>({}).E } -> std::same_as<stdx::array3d&&>;
    };

} // namespace MACE::Detector::Field
