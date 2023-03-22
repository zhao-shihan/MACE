#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/Entry/VectorEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class MCPHit {
public:
    struct Entry : NonConstructibleBase {
        using HitTime = DoubleEntry<MCPHit, 0, double>;
        using HitPosition = Vector2FEntry<MCPHit, 1, stdx::array2d>;
    };

public:
    virtual ~MCPHit() = default;

    const auto& HitTime() const { return fHitTime; }
    const auto& HitPosition() const { return fHitPosition; }

    void HitTime(auto&& v) { fHitTime.Value(std::forward<decltype(v)>(v)); }
    void HitPosition(auto&& v) { fHitPosition.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "MCPHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::HitTime fHitTime;
    Entry::HitPosition fHitPosition;
};
static_assert(TransientData<MCPHit>);

} // namespace Hit

template<>
MCPHit::Entry::HitTime::BranchSocket MCPHit::Entry::HitTime::Base::fgBranchSocket;
template<>
MCPHit::Entry::HitPosition::BranchSocket MCPHit::Entry::HitPosition::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/MCPHit.inl"
