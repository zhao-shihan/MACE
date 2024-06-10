#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

#include "muc/ceta_string"

#include <concepts>
#include <optional>

namespace MACE::Detector::Field {

/// @brief An electromagnetic field interpolated from data.
/// Initialization and interpolation are performed by `AFieldMap`.
/// @tparam ACache A string literal, can be "WithCache" or "NoCache".
/// @tparam AFieldMap A field map type, e.g. `EFM::FieldMap3D<Eigen::Vector<double, 6>>` or
/// `EFM::FieldMap3DSymZ<Eigen::Vector<double, 6>>`.
/// @note "WithCache" and "NoCache" decides whether field cache will be used.
/// "WithCache" field will reuse the field value calculated in last calculation if
/// this calculation happens exactly at the same position. In principle, "WithCache"
/// accelerates cases when there are many subsequent calls to E or B or EB with same x:
///     Something(field.E(x), field.B(x));
/// However, if these cases do not matter or you need maximum performace in EB then
/// "NoCache" would be better.
template<muc::ceta_string ACache = "WithCache", typename AFieldMap = EFM::FieldMap3D<Eigen::Vector<double, 6>>>
    requires((ACache == "WithCache" or ACache == "NoCache") and
             std::same_as<typename AFieldMap::CoordinateType, double>)
class ElectromagneticFieldMap;

template<typename AFieldMap>
class ElectromagneticFieldMap<"WithCache", AFieldMap> : public ElectromagneticFieldBase<ElectromagneticFieldMap<"WithCache", AFieldMap>>,
                                                        public AFieldMap {
private:
    template<Concept::NumericVector3D T>
    using F = typename ElectromagneticFieldBase<ElectromagneticFieldMap<"WithCache", AFieldMap>>::F<T>;

public:
    using AFieldMap::AFieldMap;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T>;

private:
    mutable Eigen::Vector3d fCachedX;
    mutable std::optional<typename AFieldMap::ValueType> fCache;
};

template<typename AFieldMap>
class ElectromagneticFieldMap<"NoCache", AFieldMap> : public ElectromagneticFieldBase<ElectromagneticFieldMap<"NoCache", AFieldMap>>,
                                                      public AFieldMap {
private:
    template<Concept::NumericVector3D T>
    using F = typename ElectromagneticFieldBase<ElectromagneticFieldMap<"NoCache", AFieldMap>>::F<T>;

public:
    using AFieldMap::AFieldMap;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T>;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/ElectromagneticFieldMap.inl"
