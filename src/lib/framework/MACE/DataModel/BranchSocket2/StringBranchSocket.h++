#pragma once

#include "MACE/DataModel/BranchSocket/BranchSocketBase2.h++"
#include "MACE/Utility/FixedString.h++"

#include <string>
#include <utility>

namespace MACE::DataModel::inline BranchSocket {

template<std::size_t AMaxSize>
class StringBranchSocket final : public BranchSocketBase2<StringBranchSocket<AMaxSize>, FixedString<AMaxSize>> {
public:
    StringBranchSocket(std::string name, std::string title, FixedString<AMaxSize> defaultString);

    const auto& Value() const { return fString; }
    void Value(auto&& v) { fString = std::forward<decltype(v)>(v); }

    void CreateBranch(TTree& tree) { this->DoCreateBranch(tree, fString.Data(), fLeafName.c_str()); }
    void ConnectToBranch(TTree& tree) { this->DoConnectToBranch(tree, fString.Data()); }

    static constexpr auto MaxSize() { return AMaxSize; }

private:
    const std::string fLeafName;
    FixedString<AMaxSize> fString;
};

using ShortStringBranchSocket2 = StringBranchSocket<15>;

} // namespace MACE::DataModel::inline BranchSocket

#include "MACE/DataModel/BranchSocket2/StringBranchSocket.inl"
