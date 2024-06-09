#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class SolenoidFieldS2 : public MagneticFieldBase<SolenoidFieldS2> {
public:
    inline SolenoidFieldS2();

    template<Concept::NumericVector3D T>
    auto B(T) const -> T { return {fSolenoid.MagneticFluxDensity(), 0, 0}; }

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidFieldS2.inl"
