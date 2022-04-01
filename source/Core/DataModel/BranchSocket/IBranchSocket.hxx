#pragma once

#include "TTree.h"

#include <type_traits>

namespace MACE::Core::DataModel::BranchSocket {

template<typename Type, bool UseReferenceInGetSet = true>
class IBranchSocket {
public:
    IBranchSocket(const TString& branchName);
    IBranchSocket(const IBranchSocket&) = delete;
    IBranchSocket& operator=(const IBranchSocket&) = delete;
    virtual ~IBranchSocket() noexcept = default;

    virtual std::conditional_t<UseReferenceInGetSet, const Type&, Type> GetValue() const = 0;
    virtual void SetValue(std::conditional_t<UseReferenceInGetSet, const Type&, Type> value) = 0;

    virtual void CreateBranch(TTree& tree) = 0;
    virtual void ConnectToBranch(TTree& tree) = 0;

protected:
    const TString fBranchName;
};

} // namespace MACE::Core::DataModel

#include "Core/DataModel/BranchSocket/IBranchSocket.ixx"
