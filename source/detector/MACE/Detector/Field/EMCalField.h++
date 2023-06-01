#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/EMCalField.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class EMCalField : public MagneticFieldBase<EMCalField<AFloat>, AFloat> {
public:
    constexpr EMCalField();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fEMCalField->MagneticFluxDensity()}; }

private:
    const Description::EMCalField* const fEMCalField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/EMCalField.inl"
