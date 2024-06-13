#pragma once

#include "MACE/Concept/InputVector.h++"
#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"

#include "muc/array"

namespace MACE::Detector::Field {

class UniformElectromagneticField : public ElectromagneticFieldBase<UniformElectromagneticField> {
public:
    constexpr UniformElectromagneticField(double bx, double by, double bz,
                                          double ex, double ey, double ez);
    template<Concept::InputVector3D T = muc::array3d>
    constexpr UniformElectromagneticField(T b, T e);

    template<Concept::NumericVector3D T>
    constexpr auto B(T) const -> T { return {fBx, fBy, fBz}; }
    template<Concept::NumericVector3D T>
    constexpr auto E(T) const -> T { return {fEx, fEy, fEz}; }
    template<Concept::NumericVector3D T>
    constexpr auto BE(T x) const -> F<T> { return {B(x), E(x)}; }

private:
    double fBx;
    double fBy;
    double fBz;
    double fEx;
    double fEy;
    double fEz;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/UniformElectromagneticField.inl"
