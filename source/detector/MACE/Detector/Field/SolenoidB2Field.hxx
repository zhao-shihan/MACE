#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Detector/Description/Solenoid.hxx"
#include "MACE/Detector/Field/MagneticFieldBase.hxx"
#include "MACE/Math/Hypot.hxx"

#include <concepts>

namespace MACE::Detector::Field {

template<std::floating_point AFloat>
class SolenoidB2Field : public MagneticFieldBase<SolenoidB2Field<AFloat>, AFloat> {
public:
    constexpr SolenoidB2Field();

    template<Concept::NumericVector3<AFloat> T>
    constexpr T BFieldAt(const T&) const;

private:
    const Description::Solenoid* const fSolenoid;
    const AFloat fX0;
    const AFloat fZ0;
    const AFloat fR0;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidB2Field.inl"
