#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class SolenoidS2Field : public MagneticFieldBase<SolenoidS2Field<AFloat>, AFloat> {
public:
    constexpr SolenoidS2Field();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {fSolenoid->MagneticFluxDensity(), 0, 0}; }

private:
    const Description::Solenoid* const fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidS2Field.inl"
