#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Detector/Field/ElectromagneticField.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Utility/VectorCast.hxx"

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
