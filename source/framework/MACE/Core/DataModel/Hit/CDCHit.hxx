#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <string_view>

namespace MACE::Core::DataModel::Hit {

class CDCHit {
public:
    inline CDCHit() noexcept;
    virtual ~CDCHit() = default;

    CDCHit(const CDCHit&) noexcept = default;
    CDCHit(CDCHit&&) noexcept = default;
    CDCHit& operator=(const CDCHit&) noexcept = default;
    CDCHit& operator=(CDCHit&&) noexcept = default;

    const auto& CellID() const { return fCellID; }
    const auto& DriftDistance() const { return fDriftDistance; }
    const auto& HitTime() const { return fHitTime; }

    void CellID(int val) { fCellID = val; }
    void DriftDistance(double d) { fDriftDistance = d; }
    void HitTime(double val) { fHitTime = val; }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("CDCHit"); }

private:
    int fCellID;
    double fDriftDistance;
    double fHitTime;

    static BranchSocket::IntBranchSocket fgCellID;
    static BranchSocket::FloatBranchSocket fgDriftDistance;
    static BranchSocket::DoubleBranchSocket fgHitTime;
};
static_assert(TransientData<CDCHit>);

} // namespace MACE::Core::DataModel::Hit

#include "MACE/Core/DataModel/Hit/CDCHit.inl"
