#pragma once

#include "MACE/Concept/MathVector.h++"
#include "MACE/Detector/Field/ElectromagneticFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

#include "muc/ceta_string"

#include <optional>

namespace MACE::Detector::Field {

/// @brief An electromagnetic field interpolated from data.
/// @tparam ACache A string literal, can be "WithCache" or "NoCache".
/// @tparam AStorageVector 6D vector type for internal stroage.
/// @note "WithCache" and "NoCache" decides whether field cache will be used.
/// "WithCache" field will reuse the field value calculated in last calculation if
/// this calculation happens exactly at the same position. In principle, "WithCache"
/// accelerates cases when there are many subsequent calls to E or B or EB with same x:
///     Something(field.E(x), field.B(x));
/// However, if these cases do not matter or you need maximum performace in EB then
/// "NoCache" would be better.
template<muc::ceta_string ACache = "WithCache", Concept::MathVector<double, 6> AStorageVector = Eigen::Vector<double, 6>>
    requires(ACache == "WithCache" or ACache == "NoCache")
class TrilerpElectromagneticField;

template<Concept::MathVector<double, 6> AStorageVector = Eigen::Vector<double, 6>>
class TrilerpElectromagneticField<"WithCache", AStorageVector> : public ElectromagneticFieldBase<TrilerpElectromagneticField<"WithCache", AStorageVector>>,
                                                                 public EFM::FieldMap3D<AStorageVector> {
private:
    template<Concept::NumericVector3D T>
    using F = typename ElectromagneticFieldBase<TrilerpElectromagneticField<"WithCache", AStorageVector>>::F<T>;

public:
    using EFM::FieldMap3D<AStorageVector>::FieldMap3D;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T>;

private:
    Eigen::Vector3d fCachedX;
    std::optional<AStorageVector> fCache;
};

template<Concept::MathVector<double, 6> AStorageVector = Eigen::Vector<double, 6>>
class TrilerpElectromagneticField<"NoCache", AStorageVector> : public ElectromagneticFieldBase<TrilerpElectromagneticField<"NoCache", AStorageVector>>,
                                                               public EFM::FieldMap3D<AStorageVector> {
private:
    template<Concept::NumericVector3D T>
    using F = typename ElectromagneticFieldBase<TrilerpElectromagneticField<"NoCache", AStorageVector>>::F<T>;

public:
    using EFM::FieldMap3D<AStorageVector>::FieldMap3D;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto E(T x) const -> T;
    template<Concept::NumericVector3D T>
    auto BE(T x) const -> F<T>;
};

} // namespace MACE::Detector::Field

#include "MACE/Detector/Field/TrilerpElectromagneticField.inl"
