#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticField.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Utility/VectorCast.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename ADerived>
class ElectromagneticFieldBase {
protected:
    constexpr ElectromagneticFieldBase() = default;
    constexpr ~ElectromagneticFieldBase() = default;

public:
    template<Concept::NumericVector3D T>
    struct F {
        T B;
        T E;
    };

public:
    template<Concept::NumericVector3D T>
    constexpr auto BEFieldAt(T x) const -> F<T>;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectromagneticFieldBase.inl"
