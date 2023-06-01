#pragma once

#include "MACE/DataModel/BranchSocketable.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include <string>
#include <utility>

namespace MACE::DataModel {

template<class ADerived, typename T>
class BranchSocketBase : public NonMoveableBase {
protected:
    BranchSocketBase(std::string branchName);
    ~BranchSocketBase() = default;

public:
    const auto& BranchName() { return fBranchName; }

protected:
    const std::string fBranchName;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/BranchSocketBase.inl"
