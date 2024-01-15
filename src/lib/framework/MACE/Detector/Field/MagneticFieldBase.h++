#pragma once

#include "MACE/Detector/Field/ElectricFieldBase.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticField.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename ADerived>
class ElectricFieldBase;

template<typename ADerived>
class MagneticFieldBase : public ElectromagneticFieldBase<ADerived> {
protected:
    constexpr MagneticFieldBase();
    constexpr ~MagneticFieldBase() = default;

public:
    template<Concept::NumericVector3D T>
    static constexpr auto EFieldAt(T) -> T { return {0, 0, 0}; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/MagneticFieldBase.inl"
