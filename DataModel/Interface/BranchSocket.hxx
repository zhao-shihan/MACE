#pragma once

#include "DataModel/Global.hxx"

template<typename Object_t, typename Address_t>
class MACE::DataModel::Interface::BranchSocket {
public:
    BranchSocket(const char* branchName);
    virtual ~BranchSocket() noexcept = default;
    BranchSocket(const BranchSocket&) = delete;
    BranchSocket& operator=(const BranchSocket&) = delete;

    [[nodiscard]] const char* BranchName() { return fBranchName; }
    [[nodiscard]] virtual Object_t& Value() = 0;
    [[nodiscard]] virtual Address_t Address() = 0;

private:
    const char* const fBranchName;
};

#include "DataModel/Interface/BranchSocket.ixx"
