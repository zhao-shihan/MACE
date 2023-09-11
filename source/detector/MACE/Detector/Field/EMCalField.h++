#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class EMCField : public MagneticFieldBase<EMCField<AFloat>, AFloat> {
public:
    constexpr EMCField();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fEMCField->MagneticFluxDensity()}; }

private:
    const Description::EMCField* const fEMCField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/EMCField.inl"
