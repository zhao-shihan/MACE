#pragma once

#include "MACE/Detector/Field/ElectricFieldBase.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticField.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename ADerived, std::floating_point AFloat>
class ElectricFieldBase;

template<typename ADerived, std::floating_point AFloat>
class MagneticFieldBase : public ElectromagneticFieldBase<ADerived, AFloat> {
protected:
    constexpr MagneticFieldBase();
    constexpr ~MagneticFieldBase() = default;

public:
    template<Concept::NumericVector3<AFloat> T>
    static constexpr T EFieldAt(const T&) { return {0, 0, 0}; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/MagneticFieldBase.inl"
