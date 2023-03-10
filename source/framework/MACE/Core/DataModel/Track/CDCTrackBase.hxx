#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"

namespace MACE::Core::DataModel::Track {

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

    static BranchSocket::IntBranchSocket fgNumHits;
    static BranchSocket::FloatBranchSocket fgChi2;
    static BranchSocket::DoubleBranchSocket fgVertexTime;
};

} // namespace MACE::Core::DataModel::Track
