#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Detector/Field/MagneticFieldMap.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

#include <variant>

namespace MACE::Detector::Field {

class EMCField : public MagneticFieldBase<EMCField> {
private:
    class FastField : public MagneticFieldBase<FastField> {
    public:
        FastField(double b);

        template<Concept::NumericVector3D T>
        auto B(T) const -> T { return {0, 0, fEMCField}; }

    private:
        double fEMCField;
    };

    using FieldMap = MagneticFieldMap<EFM::FieldMap3DSymY<Eigen::Vector3d>>;

public:
    EMCField();

    template<Concept::NumericVector3D T> // clang-format off
    auto B(T x) const -> T { return std::visit([&x](auto&& f) { return f.B(x); }, fField); } // clang-format on

private:
    std::variant<FastField, FieldMap> fField;
};

} // namespace MACE::Detector::Field
