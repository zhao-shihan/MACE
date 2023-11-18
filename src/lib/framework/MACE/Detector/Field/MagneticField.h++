#pragma once

#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Extension/stdx/arraynx.h++"

namespace MACE::Detector::Field {

template<typename F, typename AFloat>
concept MagneticField =
    requires {
        requires ElectromagneticField<F, AFloat>;
        requires F::template EFieldAt<stdx::array3<AFloat>>({}) == stdx::array3<AFloat>{0, 0, 0};
    };

} // namespace MACE::Detector::Field
