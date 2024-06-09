#pragma once

#include "MACE/Concept/MathVector.h++"
#include "MACE/Detector/Field/MagneticFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

namespace MACE::Detector::Field {

/// @brief A megnetic field interpolated from data.
/// Initialization and interpolation are performed by EFM.
/// @tparam AStorageVector 6D vector type passed to EFM for internal stroage.
template<Concept::MathVector3D AStorageVector = Eigen::Vector3d>
class TrilerpMagneticField : public MagneticFieldBase<TrilerpMagneticField<AStorageVector>>,
                             public EFM::FieldMap3D<AStorageVector> {
public:
    using EFM::FieldMap3D<AStorageVector>::FieldMap3D;

    template<Concept::NumericVector3D T>
    auto B(T x) const -> T { return VectorCast<T>((*this)(x[0], x[1], x[2])); }
};

} // namespace MACE::Detector::Field
