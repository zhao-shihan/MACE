#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/VertexDetectorHit.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::VertexDetectorSimHit :
    public MACE::DataModel::VertexDetectorHit {
    using Base = MACE::DataModel::VertexDetectorHit;
    friend MACE::DataModel::DataHub;

public:
    VertexDetectorSimHit() noexcept;
    VertexDetectorSimHit(const VertexDetectorSimHit& hit) noexcept = default;
    VertexDetectorSimHit(VertexDetectorSimHit&& hit) noexcept = default;
    virtual ~VertexDetectorSimHit() noexcept = default;
    VertexDetectorSimHit& operator=(const VertexDetectorSimHit& hit) noexcept = default;
    VertexDetectorSimHit& operator=(VertexDetectorSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetParticlePDGCode() const { return fPDGCode; }
    [[nodiscard]] const auto& GetEventID() const { return fEventID; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    void SetPDGCode(Int_t pdgCode) { fPDGCode = pdgCode; }
    void SetEventID(Int_t val) { fEventID = val; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "MCPSimHit"; }

private:
    Double_t    fVertexTime;
    TEveVectorD fVertexPosition;
    Int_t       fPDGCode;
    Int_t       fEventID;
    Int_t       fTrackID;

    static FloatBranchSocket    fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static IntBranchSocket      fgPDGCode;
    static IntBranchSocket      fgEventID;
    static IntBranchSocket      fgTrackID;
};

inline void MACE::DataModel::VertexDetectorSimHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgVertexTime.Value() = fVertexTime;
    fgVertexPosition.Value() = fVertexPosition;
    fgPDGCode.Value() = fPDGCode;
    fgEventID.Value() = fEventID;
    fgTrackID.Value() = fTrackID;
}
