#pragma once

#include "MACE/Detector/Field/ElectricField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<class ADerived, std::floating_point AFloat>
class MagneticFieldBase;

template<class ADerived, std::floating_point AFloat>
class ElectricFieldBase : public ElectromagneticFieldBase<ADerived, AFloat> {
protected:
    constexpr ElectricFieldBase();
    constexpr ~ElectricFieldBase() = default;

public:
    template<Concept::NumericVector3<AFloat> T>
    static constexpr T BFieldAt(const T&) { return {0, 0, 0}; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectricFieldBase.inl"
