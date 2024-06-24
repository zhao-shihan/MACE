#pragma once

#include "Mustard/Concept/NumericVector.h++"
#include "Mustard/Detector/Field/ElectromagneticFieldBase.h++"
#include "Mustard/Detector/Field/ElectromagneticFieldMap.h++"
#include "Mustard/Detector/Field/UniformElectromagneticField.h++"

#include <variant>

namespace MACE::Detector::Field {
class AcceleratorField : public Mustard::Detector::Field::ElectromagneticFieldBase<AcceleratorField> {
public:
    AcceleratorField();

    template<Mustard::Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); }
    template<Mustard::Concept::NumericVector3D T>
    auto E(T x) const -> T { return std::visit([&x](auto&& f) { return f.E(x); }, fField); }
    template<Mustard::Concept::NumericVector3D T>
    auto BE(T x) const -> F<T> { return std::visit([&x](auto&& f) { return f.BE(x); }, fField); } // clang-format on

private:
    class FastField : public Mustard::Detector::Field::ElectromagneticFieldBase<FastField> {
    public:
        FastField();

        template<Mustard::Concept::NumericVector3D T>
        auto B(T) const -> T { return {0, 0, fB}; }
        template<Mustard::Concept::NumericVector3D T>
        auto E(T x) const -> T { return {0, 0, x[2] < fZ0 ? fE1 : fE2}; }
        template<Mustard::Concept::NumericVector3D T>
        auto BE(T x) const -> F<T> { return {B(x), E(x)}; }

    private:
        double fB;
        double fZ0;
        double fE1;
        double fE2;
    };

    using FieldMap = Mustard::Detector::Field::ElectromagneticFieldMapSymmetryY<"NoCache">;

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
