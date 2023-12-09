#pragma once

#include "MACE/Detector/Field/ElectricField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename ADerived>
class MagneticFieldBase;

template<typename ADerived>
class ElectricFieldBase : public ElectromagneticFieldBase<ADerived> {
protected:
    constexpr ElectricFieldBase();
    constexpr ~ElectricFieldBase() = default;

public:
    template<Concept::NumericVector3D T>
    static constexpr auto BFieldAt(T) -> T { return {0, 0, 0}; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectricFieldBase.inl"
