#pragma once

#include "MACE/Concept/MathVector.h++"
#include "MACE/Concept/NumericVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "CLHEP/Units/SystemOfUnits.h"

#include "Eigen/Core"

namespace MACE::Detector::Field {

/// @brief A functional type converts B-field SI field value
/// to CLHEP unit system. Use in EFM template parameter.
struct BFieldSI2CLHEP {
    template<Concept::MathVector3D T>
    [[nodiscard]] constexpr auto operator()(T B) const -> T {
        return B * CLHEP::tesla;
    }
};

/// @brief An magnetic field interpolated from data.
/// Initialization and interpolation are performed by `AFieldMap`.
/// @tparam AFieldMap A field map type, e.g. `EFM::FieldMap3D<Eigen::Vector3d>` or
/// `EFM::FieldMap3DSymZ<Eigen::Vector3d>`.
template<typename AFieldMap = EFM::FieldMap3D<Eigen::Vector3d, double, muc::multidentity, BFieldSI2CLHEP>>
    requires std::same_as<typename AFieldMap::CoordinateType, double>
class MagneticFieldMap : public MagneticFieldBase<MagneticFieldMap<AFieldMap>>,
                         public AFieldMap {
public:
    using AFieldMap::AFieldMap;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T { return VectorCast<T>((*this)(x[0], x[1], x[2])); }
};

/// @brief An YZ plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymX = MagneticFieldMap<ACache, EFM::FieldMap3DSymX<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An ZX plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymY = MagneticFieldMap<ACache, EFM::FieldMap3DSymY<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An XY plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymZ = MagneticFieldMap<ACache, EFM::FieldMap3DSymZ<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An YZ, ZX plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymXY = MagneticFieldMap<ACache, EFM::FieldMap3DSymXY<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An XY, YZ plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymXZ = MagneticFieldMap<ACache, EFM::FieldMap3DSymXZ<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An ZX, XY plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymYZ = MagneticFieldMap<ACache, EFM::FieldMap3DSymYZ<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

/// @brief An XY, YZ, ZX plane mirror symmetry magnetic field interpolated from data.
/// @tparam ACache Use cache or not. See `MagneticFieldMap`.
template<muc::ceta_string ACache = "WithCache">
using MagneticFieldMapSymXYZ = MagneticFieldMap<ACache, EFM::FieldMap3DSymXYZ<Eigen::Vector3d, double, BFieldSI2CLHEP>>;

} // namespace MACE::Detector::Field
