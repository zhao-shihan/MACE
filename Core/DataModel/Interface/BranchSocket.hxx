#pragma once

#include "DataModel/Global.hxx"
#include "ObserverPtr.hxx"

template<typename Object_t, typename Address_t>
class MACE::DataModel::Interface::BranchSocket {
public:
    BranchSocket(const char* branchName);
    virtual ~BranchSocket() noexcept = default;
    BranchSocket(const BranchSocket&) = delete;
    BranchSocket& operator=(const BranchSocket&) = delete;

    [[nodiscard]] const char* BranchName() const { return fBranchName; }
    [[nodiscard]] virtual Object_t& Value() = 0;
    [[nodiscard]] virtual Address_t Address() = 0;

    virtual void CreateBranch(TTree& tree) { tree.Branch(fBranchName, Address()); }
    virtual void ConnectToBranch(TTree& tree) { tree.SetBranchAddress(fBranchName, Address()); }

protected:
    const char* const fBranchName;
};

#include "DataModel/Interface/BranchSocket.ixx"
