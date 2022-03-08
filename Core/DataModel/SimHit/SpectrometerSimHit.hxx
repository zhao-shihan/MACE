#pragma once

#include "DataModel/Global.hxx"
#include "DataModel/Hit/SpectrometerHit.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::SpectrometerSimHit :
    public MACE::DataModel::SpectrometerHit {
    using Base = MACE::DataModel::SpectrometerHit;
    friend MACE::DataModel::DataHub;

public:
    SpectrometerSimHit() noexcept;
    SpectrometerSimHit(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit(SpectrometerSimHit&& hit) noexcept = default;
    virtual ~SpectrometerSimHit() noexcept = default;
    SpectrometerSimHit& operator=(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit& operator=(SpectrometerSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetMomentum() const { return fMomentum; }
    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetParticlePDGCode() const { return fPDGCode; }
    [[nodiscard]] const auto& GetEventID() const { return fEventID; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    void SetMomentum(const TEveVectorD& mom) { fMomentum = mom; }
    void SetMomentum(TEveVectorD&& mom) { fMomentum = std::move(mom); }
    void SetMomentum(Double_t pX, Double_t pY, Double_t pZ) { fMomentum.Set(pX, pY, pZ); }
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
    static constexpr const char* BasicName() { return "CDCSimHit"; }

private:
    TEveVectorD fMomentum;
    Double_t    fVertexTime;
    TEveVectorD fVertexPosition;
    Int_t       fPDGCode;
    Int_t       fEventID;
    Int_t       fTrackID;

    static Vector3FBranchSocket fgMomentum;
    static DoubleBranchSocket   fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static IntBranchSocket      fgPDGCode;
    static IntBranchSocket      fgEventID;
    static IntBranchSocket      fgTrackID;
};

inline void MACE::DataModel::SpectrometerSimHit::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgMomentum.Value() = fMomentum;
    fgVertexTime.Value() = fVertexTime;
    fgVertexPosition.Value() = fVertexPosition;
    fgPDGCode.Value() = fPDGCode;
    fgEventID.Value() = fEventID;
    fgTrackID.Value() = fTrackID;
}
