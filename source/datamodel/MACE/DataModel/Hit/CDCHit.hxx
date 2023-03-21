#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/DataModel/Entry/FundamentalEntry.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel::inline Hit {

using namespace std::string_view_literals;

class CDCHit {
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
    IntEntry<CDCHit, 0, int> fCellID;
    FloatEntry<CDCHit, 1, double> fDriftDistance;
    DoubleEntry<CDCHit, 2, double> fHitTime;
};
static_assert(TransientData<CDCHit>);

} // namespace MACE::DataModel::inline Hit

#include "MACE/DataModel/Hit/CDCHit.inl"
