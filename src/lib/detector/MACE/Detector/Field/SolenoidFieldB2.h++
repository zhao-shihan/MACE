#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

namespace MACE::Detector::Field {

class SolenoidFieldB2 : public MagneticFieldBase<SolenoidFieldB2> {
public:
    inline SolenoidFieldB2();

    template<Concept::NumericVector3D T>
    inline auto BFieldAt(T) const -> T;

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidFieldB2.inl"
