#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::IntBranchSocket;

class CDCPhysicsTrack;

class ICDCSimTrack : public virtual ITransientData {
public:
    ICDCSimTrack() noexcept;
    ICDCSimTrack(const ICDCSimTrack&) noexcept = default;
    ICDCSimTrack(ICDCSimTrack&&) noexcept = default;
    virtual ~ICDCSimTrack() noexcept = 0;
    ICDCSimTrack& operator=(const ICDCSimTrack&) noexcept = default;
    ICDCSimTrack& operator=(ICDCSimTrack&&) noexcept = default;

    [[nodiscard]] const auto& GetTrueNumHits() const { return fTrueNumHits; }
    [[nodiscard]] const auto& GetTrueVertexTime() const { return fTrueVertexTime; }

    void SetTrueNumHits(Int_t n) { fTrueNumHits = n; }
    void SetTrueVertexTime(Double_t val) { fTrueVertexTime = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CDC__Base__SimTrk"; }

private:
    Int_t fTrueNumHits;
    Double_t fTrueVertexTime;

    static IntBranchSocket fgTrueNumHits;
    static DoubleBranchSocket fgTrueVertexTime;
};

} // namespace MACE::Core::DataModel::Track
