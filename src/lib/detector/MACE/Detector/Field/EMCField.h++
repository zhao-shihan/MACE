#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class EMCField : public MagneticFieldBase<EMCField> {
public:
    inline EMCField();

    template<Concept::NumericVector3D T>
    auto B(T) const -> T { return {0, 0, fEMCField.MagneticFluxDensity()}; }

private:
    const Description::EMCField& fEMCField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/EMCField.inl"
