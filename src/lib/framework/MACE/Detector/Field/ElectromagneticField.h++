#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F, typename AFloat>
concept ElectromagneticField =
    requires(const F f, stdx::array3<AFloat> x) {
        requires std::floating_point<AFloat>;
        { f.BFieldAt(x) } -> std::same_as<decltype(x)>;
        { f.EFieldAt(x) } -> std::same_as<decltype(x)>;
        { f.BEFieldAt(x) } -> std::same_as<stdx::array2<decltype(x)>>;
        { f.template BFieldAt<stdx::array3<AFloat>>({}) } -> std::same_as<stdx::array3<AFloat>>;
        { f.template EFieldAt<stdx::array3<AFloat>>({}) } -> std::same_as<stdx::array3<AFloat>>;
        { f.template BEFieldAt<stdx::array3<AFloat>>({}) } -> std::same_as<stdx::array2<stdx::array3<AFloat>>>;
    };

} // namespace MACE::Detector::Field
