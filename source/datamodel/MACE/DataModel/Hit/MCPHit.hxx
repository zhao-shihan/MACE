#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/arraynx.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class MCPHit {
public:
    struct Entry : NonConstructibleBase {
        using Time = DoubleEntry<MCPHit, 0, double>;
        using Position = Vector2FEntry<MCPHit, 1, stdx::array2d>;
    };

public:
    virtual ~MCPHit() = default;

    const auto& Time() const& { return fTime; }
    const auto& Position() const& { return fPosition; }

    auto& Time() & { return fTime; }
    auto& Position() & { return fPosition; }

    static constexpr auto BasicTreeName() { return "MCPHit"sv; }

    inline void FillAllBranchSocket() const&;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);

private:
    Entry::Time fTime;
    Entry::Position fPosition;
};
static_assert(TransientData<MCPHit>);

} // namespace Hit

template<>
MCPHit::Entry::Time::BranchSocket MCPHit::Entry::Time::Base::fgBranchSocket;
template<>
MCPHit::Entry::Position::BranchSocket MCPHit::Entry::Position::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/MCPHit.inl"
