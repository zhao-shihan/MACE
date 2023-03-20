#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"

namespace MACE::DataModel::inline Track {

class CDCSimTrackBase {
protected:
    CDCSimTrackBase() noexcept;
    ~CDCSimTrackBase() = default;

public:
    CDCSimTrackBase(const CDCSimTrackBase&) noexcept = default;
    CDCSimTrackBase(CDCSimTrackBase&&) noexcept = default;
    CDCSimTrackBase& operator=(const CDCSimTrackBase&) noexcept = default;
    CDCSimTrackBase& operator=(CDCSimTrackBase&&) noexcept = default;

    const auto& GetTrueNumHits() const { return fTrueNumHits; }
    const auto& TrueVertexTime() const { return fTrueVertexTime; }

    void SetTrueNumHits(int n) { fTrueNumHits = n; }
    void TrueVertexTime(double val) { fTrueVertexTime = val; }

protected:
    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    int fTrueNumHits;
    double fTrueVertexTime;

    static IntBranchSocket fgTrueNumHits;
    static DoubleBranchSocket fgTrueVertexTime;
};

} // namespace MACE::DataModel::inline Track
