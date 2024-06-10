#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectricFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

namespace MACE::Detector::Field {

/// @brief An electric field interpolated from data.
/// Initialization and interpolation are performed by `AFieldMap`.
/// @tparam AFieldMap A field map type, e.g. `EFM::FieldMap3D<Eigen::Vector3d>` or
/// `EFM::FieldMap3DSymZ<Eigen::Vector3d>`.
template<typename AFieldMap = EFM::FieldMap3D<Eigen::Vector3d>>
    requires std::same_as<typename AFieldMap::CoordinateType, double>
class ElectricFieldMap : public ElectricFieldBase<ElectricFieldMap<AFieldMap>>,
                         public AFieldMap {
public:
    using AFieldMap::AFieldMap;

    template<Concept::NumericVector3D T>
    auto E(T x) const -> T { return VectorCast<T>((*this)(x[0], x[1], x[2])); }
};

} // namespace MACE::Detector::Field
