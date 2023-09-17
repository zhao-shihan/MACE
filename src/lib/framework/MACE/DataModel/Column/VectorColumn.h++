#pragma once

#include "MACE/Concept/NumericVector.h++"
#include "MACE/Concept/ROOTFundamental.h++"
#include "MACE/DataModel/BranchSocket2/VectorBranchSocket2.h++"
#include "MACE/DataModel/Column/ColumnBase.h++"
#include "MACE/Utility/VectorAssign.h++"
#include "MACE/Utility/VectorCast.h++"
#include "MACE/Utility/VectorValueType.h++"

#include "RtypesCore.h"

#include <concepts>
#include <string>
#include <utility>

namespace MACE::DataModel::inline Column {

template<class AData, gsl::index AUniqueID, Concept::ROOTFundamental T, std::size_t N, Concept::NumericVectorAny<N> U>
    requires(std::integral<T> and std::integral<VectorValueType<U>>) or
            (std::floating_point<T> and std::floating_point<VectorValueType<U>>)
class VectorColumn final : public ColumnBase<VectorColumn<AData, AUniqueID, T, N, U>,
                                             AData, AUniqueID,
                                             std::array<T, N>, VectorBranchSocket2<T, N>,
                                             U> {
public:
    using Base = ColumnBase<VectorColumn<AData, AUniqueID, T, N, U>,
                            AData, AUniqueID,
                            std::array<T, N>, VectorBranchSocket2<T, N>,
                            U>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    VectorColumn();

    const auto& Value() const { return fVector; }
    template<Concept::NumericVectorAny<N> V>
    auto Value() const { return VectorCast<V>(fVector); }

    void Value(auto&& v) { fVector <<= std::forward<decltype(v)>(v); }
    void Value(U&& v) { fVector = std::forward<U>(v); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fVector); }

private:
    U fVector;
};

#define MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Type, N, Suffix)                           \
    template<class AData, gsl::index AUniqueID, Concept::NumericVectorAny<N> T>             \
        requires(std::integral<Type> and std::integral<VectorValueType<T>>) or              \
                    (std::floating_point<Type> and std::floating_point<VectorValueType<T>>) \
    using Vector##N##Suffix##Column = VectorColumn<AData, AUniqueID, Type, N, T>;

MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 2, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 3, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 4, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 2, D)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 3, D)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 4, D)

#undef MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS

} // namespace MACE::DataModel::inline Column

#include "MACE/DataModel/Column/VectorColumn.inl"
