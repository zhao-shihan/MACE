#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"

namespace MACE::Detector::Field {

class SpectrometerField : public MagneticFieldBase<SpectrometerField> {
public:
    inline SpectrometerField();

    template<Concept::NumericVector3D T>
    auto BFieldAt(T) const -> T { return {0, 0, fSpectrometerField.MagneticFluxDensity()}; }

private:
    const Description::SpectrometerField& fSpectrometerField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/SpectrometerField.inl"
