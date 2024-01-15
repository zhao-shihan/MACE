#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Math/Norm.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"

namespace MACE::Detector::Field {

class SolenoidB2Field : public MagneticFieldBase<SolenoidB2Field> {
public:
    inline SolenoidB2Field();

    template<Concept::NumericVector3D T>
    inline auto BFieldAt(T) const -> T;

private:
    const Description::Solenoid& fSolenoid;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SolenoidB2Field.inl"
