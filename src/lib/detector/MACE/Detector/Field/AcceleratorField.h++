#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"

namespace MACE::Detector::Field {

class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField> {
public:
    inline AcceleratorField();

    template<Concept::NumericVector3D T>
    auto BFieldAt(T) const -> T { return {0, 0, fMMSField.MagneticFluxDensity()}; }
    template<Concept::NumericVector3D T>
    auto EFieldAt(T) const -> T { return {0, 0, fAcceleratorField.AcceleratorFieldStrength()}; }

private:
    const Description::MMSField& fMMSField;
    const Description::AcceleratorField& fAcceleratorField;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/AcceleratorField.inl"
