#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class SolenoidS2Field : public MagneticFieldBase<SolenoidS2Field> {
public:
    inline SolenoidS2Field();

    template<Concept::NumericVector3D T>
    auto BFieldAt(T) const -> T { return {fSolenoid.MagneticFluxDensity(), 0, 0}; }

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidS2Field.inl"
