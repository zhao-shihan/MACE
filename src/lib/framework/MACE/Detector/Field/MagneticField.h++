#pragma once

#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Extension/stdx/arraynx.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F>
concept MagneticField =
    requires {
        requires ElectromagneticField<F>;
        { F::template EFieldAt<stdx::array3d>({}) } -> std::same_as<stdx::array3d>;
        requires F::template EFieldAt<stdx::array3d>({}) == stdx::array3d{};
    };

} // namespace MACE::Detector::Field
