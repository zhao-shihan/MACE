#pragma once

#include "MACE/Concept/MathVector.h++"
#include "MACE/Detector/Field/ElectricFieldBase.h++"
#include "MACE/Utility/VectorCast.h++"

#include "EFM/FieldMap3D.h++"

#include "Eigen/Core"

namespace MACE::Detector::Field {

template<Concept::MathVector3D AStorageVector = Eigen::Vector3d>
class TrilerpElectricField : public ElectricFieldBase<TrilerpElectricField<AStorageVector>>,
                             public EFM::FieldMap3D<AStorageVector> {
public:
    using EFM::FieldMap3D<AStorageVector>::FieldMap3D;

    template<Concept::NumericVector3D T>
    auto E(T x) const -> T { return VectorCast<T>((*this)(x[0], x[1], x[2])); }
};

} // namespace MACE::Detector::Field
