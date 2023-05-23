#pragma once

#include "MACE/Detector/Field/ElectromagneticField.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"

namespace MACE::Detector::Field {

template<class F, typename AFloat>
concept MagneticField =
    requires {
        requires ElectromagneticField<F, AFloat>;
        requires F::template EFieldAt<stdx::array3<AFloat>>({}) == stdx::array3<AFloat>{0, 0, 0};
    };

} // namespace MACE::Detector::Field
