#pragma once

#include "MACE/Core/DataModel/BranchSocketable.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include "TTree.h"

#include <string>
#include <type_traits>

namespace MACE::Core::DataModel {

template<class ADerived, typename T>
class BranchSocketBase : public Utility::NonMoveableBase {
protected:
    BranchSocketBase(const std::string& branchName);
    ~BranchSocketBase() = default;

protected:
    const std::string fBranchName;
};

} // namespace MACE::Core::DataModel

#include "MACE/Core/DataModel/BranchSocketBase.inl"
