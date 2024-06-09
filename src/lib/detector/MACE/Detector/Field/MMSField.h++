#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class MMSField : public MagneticFieldBase<MMSField> {
public:
    inline MMSField();

    template<Concept::NumericVector3D T>
    auto B(T) const -> T { return {0, 0, fMMSField.MagneticFluxDensity()}; }

private:
    const Description::MMSField& fMMSField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/MMSField.inl"
