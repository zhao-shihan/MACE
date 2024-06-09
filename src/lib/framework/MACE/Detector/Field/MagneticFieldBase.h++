#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectricFieldBase.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticField.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<typename ADerived>
class ElectricFieldBase;

template<typename ADerived>
class MagneticFieldBase : public ElectromagneticFieldBase<ADerived> {
private:
    template<Concept::NumericVector3D T>
    using F = typename ElectromagneticFieldBase<ADerived>::F<T>;

protected:
    constexpr MagneticFieldBase();
    constexpr ~MagneticFieldBase() = default;

public:
    template<Concept::NumericVector3D T>
    static constexpr auto E(T) -> T { return {0, 0, 0}; }
    template<Concept::NumericVector3D T>
    constexpr auto BE(T x) const -> F<T> { return {static_cast<const ADerived*>(this)->B(x), E(x)}; }
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/MagneticFieldBase.inl"
