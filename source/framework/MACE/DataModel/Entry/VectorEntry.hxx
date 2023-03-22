#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Concept/ROOTFundamental.hxx"
#include "MACE/DataModel/BranchSocket2/VectorBranchSocket2.hxx"
#include "MACE/DataModel/EntryBase.hxx"
#include "MACE/Utility/ValueTypeOf.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "RtypesCore.h"

#include <concepts>
#include <string>
#include <utility>

namespace MACE::DataModel::inline Entry {

template<class AData, gsl::index ABranchID, Concept::ROOTFundamental T, std::size_t N, Concept::NumericVectorAny<N> U>
    requires(std::integral<T> and std::integral<ValueTypeOf<U>>) or
            (std::floating_point<T> and std::floating_point<ValueTypeOf<U>>)
class VectorEntry final : public EntryBase<VectorEntry<AData, ABranchID, T, N, U>,
                                           AData, ABranchID,
                                           std::array<T, N>, VectorBranchSocket2<T, N>,
                                           U> {
public:
    using Base = EntryBase<VectorEntry<AData, ABranchID, T, N, U>,
                           AData, ABranchID,
                           std::array<T, N>, VectorBranchSocket2<T, N>,
                           U>;
    using BranchSocket = decltype(Base::fgBranchSocket);

public:
    VectorEntry();

    const auto& Value() const { return fVector; }
    template<Concept::NumericVectorAny<N> V>
    auto Value() const { return VectorCast<V>(fVector); }
    void Value(auto&& v) { VectorAssign(fVector, std::forward<decltype(v)>(v)); }

    void FillBranchSocket() const { this->fgBranchSocket.Value(fVector); }

private:
    U fVector;
};

#define MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Type, N, Suffix)                       \
    template<class AData, gsl::index ABranchID, Concept::NumericVectorAny<N> T>         \
        requires(std::integral<Type> and std::integral<ValueTypeOf<T>>) or              \
                    (std::floating_point<Type> and std::floating_point<ValueTypeOf<T>>) \
    using Vector##N##Suffix##Entry = VectorEntry<AData, ABranchID, Type, N, T>;

MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 2, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 3, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Float_t, 4, F)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 2, D)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 3, D)
MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS(Double_t, 4, D)

#undef MACE_DATA_MODEL_ENTRY_VECTOR_ENTRY_ALIAS

} // namespace MACE::DataModel::inline Entry

#include "MACE/DataModel/Entry/VectorEntry.inl"
