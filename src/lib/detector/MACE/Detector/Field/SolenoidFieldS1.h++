#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class SolenoidFieldS1 : public MagneticFieldBase<SolenoidFieldS1> {
public:
    inline SolenoidFieldS1();

    template<Concept::NumericVector3D T>
    auto BFieldAt(T) const -> T { return {0, 0, fSolenoid.MagneticFluxDensity()}; }

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidFieldS1.inl"
