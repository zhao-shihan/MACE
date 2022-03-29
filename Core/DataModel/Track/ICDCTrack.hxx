#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;

class CDCPhysicsTrack;

class ICDCTrack : public virtual ITransientData {
public:
    ICDCTrack() noexcept;
    ICDCTrack(const ICDCTrack&) noexcept = default;
    ICDCTrack(ICDCTrack&&) noexcept = default;
    virtual ~ICDCTrack() noexcept = 0;
    ICDCTrack& operator=(const ICDCTrack&) noexcept = default;
    ICDCTrack& operator=(ICDCTrack&&) noexcept = default;

    [[nodiscard]] const auto& GetNumHits() const { return fNumHits; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }
    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }

    void SetNumHits(Int_t n) { fNumHits = n; }
    void SetChi2(Double_t val) { fChi2 = val; }
    void SetVertexTime(Double_t val) { fVertexTime = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CDC__Base__Trk"; }

private:
    Int_t fNumHits;
    Double_t fChi2;
    Double_t fVertexTime;

    static IntBranchSocket fgNumHits;
    static FloatBranchSocket fgChi2;
    static DoubleBranchSocket fgVertexTime;
};

} // namespace MACE::Core::DataModel::Track
