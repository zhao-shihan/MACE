#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/TrilerpElectromagneticField.h++"

#include <variant>

namespace MACE::Detector::Field {

class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField> {
private:
    class FastField : public ElectromagneticFieldBase<FastField> {
    public:
        FastField();

        template<Concept::NumericVector3D T>
        auto B(T) const -> T { return {0, 0, fMMSField.MagneticFluxDensity()}; }
        template<Concept::NumericVector3D T>
        auto E(T) const -> T { return {0, 0, fAccelerator.AcceleratePotential() / fAccelerator.AccelerateLength()}; }
        template<Concept::NumericVector3D T>
        auto BE(T x) const -> F<T> { return {B(x), E(x)}; }

    private:
        const Description::MMSField& fMMSField;
        const Description::Accelerator& fAccelerator;
    };

    using TrilerpField = TrilerpElectromagneticField<"NoCache">;

public:
    AcceleratorField() = default;
    AcceleratorField(std::string_view fileName, std::string_view nTupleName);

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T { return std::visit([&x](auto&& f) { return f.E(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T> { return std::visit([&x](auto&& f) { return f.BE(x); }, fField); } // clang-format on

private:
    std::variant<FastField, TrilerpField> fField;
};

} // namespace MACE::Detector::Field
