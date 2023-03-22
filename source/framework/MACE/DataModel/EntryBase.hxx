#pragma once

#include "MACE/DataModel/BranchSocketable2.hxx"

#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <string>

namespace MACE::DataModel {

template<class ADerived,
         class AData, gsl::index ABranchID,
         typename T, BranchSocketable2<T> ABranchSocket,
         typename U>
    requires(ABranchID >= 0)
class EntryBase {
protected:
    EntryBase();
    ~EntryBase() = default;

public:
    static auto BranchID() { return ABranchID; }
    static const auto& Name() { return fgBranchSocket.Name(); }

    static void CreateBranch(TTree& tree) { fgBranchSocket.CreateBranch(tree); }
    static void ConnectToBranch(TTree& tree) { fgBranchSocket.ConnectToBranch(tree); }

protected:
    static ABranchSocket fgBranchSocket;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/EntryBase.inl"
