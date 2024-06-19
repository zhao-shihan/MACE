#pragma once

#include "Mustard/Concept/NumericVector.h++"
#include "Mustard/Detector/Field/MagneticFieldBase.h++"
#include "Mustard/Detector/Field/MagneticFieldMap.h++"
#include "Mustard/Detector/Field/UniformMagneticField.h++"

#include <variant>

namespace MACE::Detector::Field {

class SolenoidFieldS2 : public Mustard::Detector::Field::MagneticFieldBase<SolenoidFieldS2> {
public:
    SolenoidFieldS2();

    template<Mustard::Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); } // clang-format on

private:
    using FastField = Mustard::Detector::Field::UniformMagneticField;
    using FieldMap = Mustard::Detector::Field::MagneticFieldMapSymmetryY<>;

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
