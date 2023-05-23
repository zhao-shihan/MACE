#pragma once

#include "MACE/DataModel/BranchSocket2/BranchSocket2.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "TTree.h"

#include <functional>
#include <string>
#include <utility>

namespace MACE::DataModel {

template<class ADerived, typename T>
class BranchSocketBase2 : public NonMoveableBase {
protected:
    BranchSocketBase2(std::string name, std::string title);
    ~BranchSocketBase2() = default;

public:
    const auto& Name() const { return fName; }
    const auto& Title() const { return fTitle; }

protected:
    void DoCreateBranch(TTree& tree, auto&&... args) { tree.Branch(fName.c_str(), args...)->SetTitle(fTitle.c_str()); }
    void DoConnectToBranch(TTree& tree, auto&&... args) { tree.SetBranchAddress(fName.c_str(), args...); }

private:
    const std::string fName;
    const std::string fTitle;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/BranchSocket2/BranchSocketBase2.inl"
