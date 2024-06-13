#pragma once

#include "MACE/Concept/InputVector.h++"
#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectricFieldBase.h++"

namespace MACE::Detector::Field {

class UniformElectricField : public ElectricFieldBase<UniformElectricField> {
public:
    constexpr UniformElectricField(double ex, double ey, double ez);
    template<Concept::InputVector3D T = muc::array3d>
    constexpr UniformElectricField(T e);

    template<Concept::NumericVector3D T>
    constexpr auto E(T) const -> T { return {fEx, fEy, fEz}; }

private:
    double fEx;
    double fEy;
    double fEz;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/UniformElectricField.inl"
