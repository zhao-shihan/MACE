#pragma once

#include "TTree.h"

#include <type_traits>

namespace MACE::Core::DataModel {

template<typename Type, bool UseReferenceInGetAndSet = true>
class IBranchSocket {
public:
    IBranchSocket() = default;
    IBranchSocket(const IBranchSocket&) = delete;
    IBranchSocket& operator=(const IBranchSocket&) = delete;
    virtual ~IBranchSocket() noexcept = default;

    [[nodiscard]] virtual std::conditional_t<UseReferenceInGetAndSet, const Type&, Type> GetValue() const = 0;
    virtual void SetValue(std::conditional_t<UseReferenceInGetAndSet, const Type&, Type> value) = 0;

    virtual void CreateBranch(TTree& tree) = 0;
    virtual void ConnectToBranch(TTree& tree) = 0;
};

} // namespace MACE::Core::DataModel
