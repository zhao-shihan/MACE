#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticFieldMap.h++"
#include "MACE/Detector/Field/ToroidField.h++"

#include <variant>

namespace MACE::Detector::Field {

class SolenoidFieldB2 : public MagneticFieldBase<SolenoidFieldB2> {
public:
    SolenoidFieldB2();

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); } // clang-format on

private:
    using FastField = ToroidField;
    using FieldMap = MagneticFieldMapSymY;

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
