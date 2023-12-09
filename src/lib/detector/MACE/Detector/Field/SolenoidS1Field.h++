#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class SolenoidS1Field : public MagneticFieldBase<SolenoidS1Field> {
public:
    inline SolenoidS1Field();

    template<Concept::NumericVector3D T>
    auto BFieldAt(T) const -> T { return {0, 0, fSolenoid.MagneticFluxDensity()}; }

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidS1Field.inl"
