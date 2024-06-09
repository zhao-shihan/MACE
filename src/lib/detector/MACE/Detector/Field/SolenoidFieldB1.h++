#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

namespace MACE::Detector::Field {

class SolenoidFieldB1 : public MagneticFieldBase<SolenoidFieldB1> {
public:
    inline SolenoidFieldB1();

    template<Concept::NumericVector3D T>
    inline auto B(T) const -> T;

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidFieldB1.inl"
