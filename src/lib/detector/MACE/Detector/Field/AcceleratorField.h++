#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"

namespace MACE::Detector::Field {

class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField> {
public:
    inline AcceleratorField();

    template<Concept::NumericVector3D T>
    auto B(T) const -> T { return {0, 0, fMMSField.MagneticFluxDensity()}; }
    template<Concept::NumericVector3D T>
    auto E(T) const -> T { return {0, 0, fAccelerator.AcceleratePotential() / fAccelerator.AccelerateLength()}; }

private:
    const Description::MMSField& fMMSField;
    const Description::Accelerator& fAccelerator;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/AcceleratorField.inl"
