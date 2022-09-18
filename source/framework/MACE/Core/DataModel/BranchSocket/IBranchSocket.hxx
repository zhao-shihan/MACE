#pragma once

#include "TTree.h"

#include "MACE/Utility/NonMoveableBase.hxx"
#include <type_traits>

namespace MACE::Core::DataModel::BranchSocket {

template<typename T, bool PassByReference = true>
class IBranchSocket : public Utility::NonMoveableBase {
public:
    IBranchSocket(const TString& branchName);
    virtual ~IBranchSocket() noexcept = default;

    virtual std::conditional_t<PassByReference, const T&, T> Value() const = 0;
    virtual void Value(std::conditional_t<PassByReference, const T&, T> value) = 0;

    virtual void CreateBranch(TTree& tree) = 0;
    virtual void ConnectToBranch(TTree& tree) = 0;

protected:
    const TString fBranchName;
};

} // namespace MACE::Core::DataModel::BranchSocket

#include "MACE/Core/DataModel/BranchSocket/IBranchSocket.inl"
