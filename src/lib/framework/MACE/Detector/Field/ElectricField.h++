#pragma once

#include "MACE/Detector/Field/ElectromagneticField.h++"

#include "muc/array"

#include <concepts>

namespace MACE::Detector::Field {

template<typename F>
concept ElectricField =
    requires {
        requires ElectromagneticField<F>;
        { F::template BFieldAt<muc::array3d>({}) } -> std::same_as<muc::array3d>;
        requires F::template BFieldAt<muc::array3d>({}) == muc::array3d{};
    };

} // namespace MACE::Detector::Field
