#pragma once

#include "MACE/Detector/Field/ElectricFieldBase.hxx"
#include "MACE/Detector/Field/ElectromagneticFieldBase.hxx"
#include "MACE/Detector/Field/MagneticField.hxx"

#include <concepts>

namespace MACE::Detector::Field {

template<class ADerived, std::floating_point AFloat>
class ElectricFieldBase;

template<class ADerived, std::floating_point AFloat>
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
