#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class UniformMagneticField : public MagneticFieldBase<UniformMagneticField> {
public:
    constexpr UniformMagneticField(double bx, double by, double bz);

    template<Concept::NumericVector3D T>
    constexpr auto B(T) const -> T { return {fBx, fBy, fBz}; }

private:
    double fBx;
    double fBy;
    double fBz;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/UniformMagneticField.inl"
