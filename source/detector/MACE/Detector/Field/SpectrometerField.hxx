#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Field/MagneticFieldBase.hxx"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class SpectrometerField : public MagneticFieldBase<SpectrometerField<AFloat>, AFloat> {
public:
    constexpr SpectrometerField();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fSpectrometerField->MagneticFluxDensity()}; }

private:
    const Description::SpectrometerField* const fSpectrometerField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SpectrometerField.inl"
