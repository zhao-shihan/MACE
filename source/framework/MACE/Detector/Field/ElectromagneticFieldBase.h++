#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorCast.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<class ADerived, std::floating_point AFloat>
class ElectromagneticFieldBase {
protected:
    constexpr ElectromagneticFieldBase();
    constexpr ~ElectromagneticFieldBase() = default;

public:
    template<Concept::NumericVector3<AFloat> T>
    constexpr stdx::array2<T> BEFieldAt(const T& x) const;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectromagneticFieldBase.inl"
