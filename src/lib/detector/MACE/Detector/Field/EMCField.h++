#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticFieldMap.h++"
#include "MACE/Detector/Field/UniformMagneticField.h++"

#include <variant>

namespace MACE::Detector::Field {

class EMCField : public MagneticFieldBase<EMCField> {
private:
    using FastField = UniformMagneticField;
    using FieldMap = MagneticFieldMapSymY;

public:
    EMCField();

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); } // clang-format on

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
