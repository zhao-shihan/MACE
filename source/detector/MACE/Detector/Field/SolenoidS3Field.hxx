#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Field/MagneticFieldBase.hxx"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class SolenoidS3Field : public MagneticFieldBase<SolenoidS3Field<AFloat>, AFloat> {
public:
    constexpr SolenoidS3Field();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const { return {0, 0, fSolenoid->MagneticFluxDensity()}; }

private:
    const Description::Solenoid* const fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidS3Field.inl"
