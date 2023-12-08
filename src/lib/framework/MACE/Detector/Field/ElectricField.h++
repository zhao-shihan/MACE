#pragma once

#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F, typename AFloat>
concept ElectricField =
    requires {
        requires ElectromagneticField<F, AFloat>;
        { F::template BFieldAt<stdx::array3<AFloat>>({}) } -> std::same_as<stdx::array3<AFloat>>;
        requires F::template BFieldAt<stdx::array3<AFloat>>({}) == stdx::array3<AFloat>{};
    };

} // namespace MACE::Detector::Field
