#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticField.h++"

#include "muc/array"

#include <concepts>

namespace MACE::Detector::Field {

namespace internal {

template<Concept::NumericVector3D T>
struct BEFieldValue {
    T B;
    T E;
};

} // namespace internal

template<typename ADerived>
class ElectromagneticFieldBase {
public:
    template<Concept::NumericVector3D T>
    using F = internal::BEFieldValue<T>;

protected:
    constexpr ElectromagneticFieldBase();
    constexpr ~ElectromagneticFieldBase() = default;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectromagneticFieldBase.inl"
