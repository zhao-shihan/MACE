#pragma once

#include "MACE/DataModel/BranchSocketable.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "TTree.h"

#include <string>
#include <type_traits>

namespace MACE::DataModel {

template<class ADerived, typename T>
class BranchSocketBase : public NonMoveableBase {
protected:
    BranchSocketBase(const std::string& branchName);
    ~BranchSocketBase() = default;

protected:
    const std::string fBranchName;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/BranchSocketBase.inl"
