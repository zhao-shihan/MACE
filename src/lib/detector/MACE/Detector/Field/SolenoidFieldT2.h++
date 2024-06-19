#pragma once

#include "Mustard/Concept/NumericVector.h++"
#include "Mustard/Detector/Field/MagneticFieldBase.h++"
#include "Mustard/Detector/Field/MagneticFieldMap.h++"
#include "Mustard/Detector/Field/ToroidField.h++"

#include <variant>

namespace MACE::Detector::Field {

class SolenoidFieldT2 : public Mustard::Detector::Field::MagneticFieldBase<SolenoidFieldT2> {
public:
    SolenoidFieldT2();

    template<Mustard::Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); } // clang-format on

private:
    using FastField = Mustard::Detector::Field::ToroidField;
    using FieldMap = Mustard::Detector::Field::MagneticFieldMapSymmetryY<>;

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
