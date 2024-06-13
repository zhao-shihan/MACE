#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Detector/Field/ElectromagneticFieldMap.h++"
#include "MACE/Detector/Field/UniformElectromagneticField.h++"

#include <variant>

namespace MACE::Detector::Field {
class AcceleratorField : public ElectromagneticFieldBase<AcceleratorField> {
public:
    AcceleratorField();

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T { return std::visit([&x](auto&& f) { return f.E(x); }, fField); }
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T> { return std::visit([&x](auto&& f) { return f.BE(x); }, fField); } // clang-format on

private:
    using FastField = UniformElectromagneticField;
    using FieldMap = ElectromagneticFieldMapSymY<"NoCache">;

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
