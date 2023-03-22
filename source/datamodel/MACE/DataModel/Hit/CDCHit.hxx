#pragma once

#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel {

inline namespace Hit {

using namespace std::string_view_literals;

class CDCHit {
public:
    struct Entry : NonConstructibleBase {
        using CellID = IntEntry<CDCHit, 0, int>;
        using DriftDistance = FloatEntry<CDCHit, 1, double>;
        using HitTime = DoubleEntry<CDCHit, 2, double>;
    };

public:
    virtual ~CDCHit() = default;

    const auto& CellID() const { return fCellID; }
    const auto& DriftDistance() const { return fDriftDistance; }
    const auto& HitTime() const { return fHitTime; }

    void CellID(auto&& v) & { fCellID.Value(std::forward<decltype(v)>(v)); }
    void DriftDistance(auto&& v) & { fDriftDistance.Value(std::forward<decltype(v)>(v)); }
    void HitTime(auto&& v) & { fHitTime.Value(std::forward<decltype(v)>(v)); }

    static constexpr auto BasicTreeName() { return "CDCHit"sv; }

    inline void FillBranchSockets() const;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    Entry::CellID fCellID;
    Entry::DriftDistance fDriftDistance;
    Entry::HitTime fHitTime;
};
static_assert(TransientData<CDCHit>);

} // namespace Hit

template<>
CDCHit::Entry::CellID::BranchSocket CDCHit::Entry::CellID::Base::fgBranchSocket;
template<>
CDCHit::Entry::DriftDistance::BranchSocket CDCHit::Entry::DriftDistance::Base::fgBranchSocket;
template<>
CDCHit::Entry::HitTime::BranchSocket CDCHit::Entry::HitTime::Base::fgBranchSocket;

} // namespace MACE::DataModel

#include "MACE/DataModel/Hit/CDCHit.inl"
