#pragma once

#include "MACE/DataModel/BranchSocket2/BranchSocket2.hxx"

#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <string>

namespace MACE::DataModel {

template<class ADerived,
         class AData, gsl::index AUniqueID,
         typename T, BranchSocket2<T> ABranchSocket,
         typename U>
    requires(AUniqueID >= 0)
class FieldBase {
protected:
    FieldBase();
    ~FieldBase() = default;

public:
    static const auto& Name() { return fgBranchSocket.Name(); }

    static void CreateBranch(TTree& tree) { fgBranchSocket.CreateBranch(tree); }
    static void ConnectToBranch(TTree& tree) { fgBranchSocket.ConnectToBranch(tree); }

protected:
    static ABranchSocket fgBranchSocket;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/Field/FieldBase.inl"
