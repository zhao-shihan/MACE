#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField<AFloat>, AFloat> {
public:
    constexpr AcceleratorField();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fSpectrometerField->MagneticFluxDensity()}; }
    template<Concept::NumericVector3<AFloat> T>
    constexpr T EFieldAt(const T&) const { return {0, 0, fAcceleratorField->AcceleratorFieldStrength()}; }

private:
    const Description::SpectrometerField* const fSpectrometerField;
    const Description::AcceleratorField* const fAcceleratorField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/AcceleratorField.inl"
