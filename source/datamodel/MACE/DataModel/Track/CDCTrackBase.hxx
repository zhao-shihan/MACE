#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"

namespace MACE::DataModel::inline Track {

class CDCTrackBase {
protected:
    CDCTrackBase() noexcept;
    ~CDCTrackBase() = default;

public:
    CDCTrackBase(const CDCTrackBase&) noexcept = default;
    CDCTrackBase(CDCTrackBase&&) noexcept = default;
    CDCTrackBase& operator=(const CDCTrackBase&) noexcept = default;
    CDCTrackBase& operator=(CDCTrackBase&&) noexcept = default;

    const auto& GetNumHits() const { return fNumHits; }
    const auto& GetChi2() const { return fChi2; }
    const auto& VertexTime() const { return fVertexTime; }

    void SetNumHits(int n) { fNumHits = n; }
    void SetChi2(double val) { fChi2 = val; }
    void VertexTime(double val) { fVertexTime = val; }

protected:
    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);

private:
    int fNumHits;
    double fChi2;
    double fVertexTime;

    static IntBranchSocket fgNumHits;
    static FloatBranchSocket fgChi2;
    static DoubleBranchSocket fgVertexTime;
};

} // namespace MACE::DataModel::inline Track
