#pragma once

#include "MACE/DataModel/BranchSocket2/BranchSocket2.h++"
#include "MACE/DataModel/Column/internal/ColumnSignatureBase.h++"

#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <string>

namespace MACE::DataModel::inline Column {

template<typename ADerived,
         class AData, gsl::index AUniqueID,
         typename T, BranchSocket2<T> ABranchSocket,
         typename U>
    requires(AUniqueID >= 0)
class ColumnBase : public internal::ColumnSignatureBase {
protected:
    constexpr ColumnBase();
    constexpr ~ColumnBase() = default;

public:
    static const auto& Name() { return fgBranchSocket.Name(); }

    static void CreateBranch(TTree& tree) { fgBranchSocket.CreateBranch(tree); }
    static void ConnectToBranch(TTree& tree) { fgBranchSocket.ConnectToBranch(tree); }

protected:
    static ABranchSocket fgBranchSocket;
};

} // namespace MACE::DataModel::inline Column

#include "MACE/DataModel/Column/ColumnBase.inl"
