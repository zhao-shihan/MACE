#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class SolenoidS1Field : public MagneticFieldBase<SolenoidS1Field<AFloat>, AFloat> {
public:
    constexpr SolenoidS1Field();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fSolenoid->MagneticFluxDensity()}; }

private:
    const Description::Solenoid* const fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidS1Field.inl"
