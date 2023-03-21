#pragma once

#include "MACE/DataModel/BranchSocketable2.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"

#include <string>
#include <utility>

namespace MACE::DataModel {

template<class ADerived, typename T>
class BranchSocketBase2 : public NonMoveableBase {
protected:
    BranchSocketBase2(std::string name);
    ~BranchSocketBase2() = default;

public:
    const auto& Name() const { return fName; }

protected:
    const std::string fName;
};

} // namespace MACE::DataModel

#include "MACE/DataModel/BranchSocketBase2.inl"
