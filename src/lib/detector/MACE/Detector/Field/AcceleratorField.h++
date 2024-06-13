#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/ElectromagneticFieldMap.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

#include <variant>

namespace MACE::Detector::Field {
class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField> {
private:
    class FastField : public ElectromagneticFieldBase<FastField> {
    public:
        FastField(double b, double e);

        template<Concept::NumericVector3D T>
        auto B(T) const -> T { return {0, 0, fB}; }
        template<Concept::NumericVector3D T>
        auto E(T) const -> T { return {0, 0, fE}; }
        template<Concept::NumericVector3D T>
        auto BE(T x) const -> F<T> { return {B(x), E(x)}; }

    private:
        double fB;
        double fE;
    };

    using FieldMap = ElectromagneticFieldMapSymY<"NoCache">;

public:
    AcceleratorField();

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T { return std::visit([&x](auto&& f) { return f.E(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T> { return std::visit([&x](auto&& f) { return f.BE(x); }, fField); } // clang-format on

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
