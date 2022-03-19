#pragma once

#include "DataModel/Global.hxx"

template<typename Type, bool UseReferenceInGetAndSet = true>
class MACE::DataModel::Interface::BranchSocket {
public:
    BranchSocket() = default;
    virtual ~BranchSocket() noexcept = default;
    BranchSocket(const BranchSocket&) = delete;
    BranchSocket& operator=(const BranchSocket&) = delete;

    [[nodiscard]] virtual std::conditional_t<UseReferenceInGetAndSet, const Type&, Type> GetValue() const = 0;
    virtual void SetValue(std::conditional_t<UseReferenceInGetAndSet, const Type&, Type> value) = 0;

    virtual void CreateBranch(TTree& tree) = 0;
    virtual void ConnectToBranch(TTree& tree) = 0;
};
