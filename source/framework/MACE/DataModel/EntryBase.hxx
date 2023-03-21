#pragma once

#include "MACE/DataModel/BranchSocketable2.hxx"

#include "TTree.h"

#include "gsl/gsl"

#include <concepts>
#include <string>

namespace MACE::DataModel {

template<class ADerived,
         class AData, gsl::index BranchIndex,
         typename T, BranchSocketable2<T> ABranchSocket,
         typename U>
class EntryBase {
protected:
    explicit EntryBase(U branchSocketValue);
    ~EntryBase() = default;

public:
    const auto& Value() const { return fValue; }
    void Value(auto&& v) & { fValue = std::forward<decltype(v)>(v); }

    static const auto& Name() { return fgBranchSocket.Name(); }

    void FillBranchSocket() const { fgBranchSocket.Value(fValue); }
    static void CreateBranch(TTree& tree) { fgBranchSocket.CreateBranch(tree); }
    static void ConnectToBranch(TTree& tree) { fgBranchSocket.ConnectToBranch(tree); }

private:
    U fValue;

protected:
    static ABranchSocket fgBranchSocket;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/EntryBase.inl"
