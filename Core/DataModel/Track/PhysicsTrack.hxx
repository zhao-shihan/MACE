#pragma once

#include "TEveVector.h"

#include "DataModel/Interface/Transient.hxx"
#include "DataModel/BranchSocket/BasicBranchSocket.hxx"
#include "DataModel/BranchSocket/ClassBranchSocket.hxx"

class MACE::DataModel::PhysicsTrack :
    public MACE::DataModel::Interface::Transient {
    using Base = MACE::DataModel::Interface::Transient;
    friend MACE::DataModel::DataHub;

public:
    PhysicsTrack() noexcept;
    PhysicsTrack(const PhysicsTrack&) noexcept = default;
    PhysicsTrack(PhysicsTrack&&) noexcept = default;
    virtual ~PhysicsTrack() noexcept = default;
    PhysicsTrack& operator=(const PhysicsTrack&) noexcept = default;
    PhysicsTrack& operator=(PhysicsTrack&&) noexcept = default;

    PhysicsTrack(const HelixTrack& helix, UInt_t absQ, Double_t B);

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetMomentum() const { return fMomentum; }
    [[nodiscard]] const auto& GetCharge() const { return fCharge; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    void SetMomentum(const TEveVectorD& mom) { fVertexPosition = mom; }
    void SetMomentum(TEveVectorD&& mom) { fVertexPosition = std::move(mom); }
    void SetMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexPosition.Set(pX, pY, pZ); }
    void SetCharge(Int_t q) { fCharge = q; }
    void SetChi2(Double_t val) { fChi2 = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "PhyTrk"; }

private:
    Double_t    fVertexTime;
    TEveVectorD fVertexPosition;
    TEveVectorD fMomentum;
    Int_t       fCharge;
    Double_t    fChi2;

    static DoubleBranchSocket   fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static Vector3FBranchSocket fgMomentum;
    static IntBranchSocket      fgCharge;
    static FloatBranchSocket    fgChi2;
};

inline void MACE::DataModel::PhysicsTrack::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgVertexTime.Value() = fVertexTime;
    fgVertexPosition.Value() = fVertexPosition;
    fgMomentum.Value() = fMomentum;
    fgCharge.Value() = fCharge;
    fgChi2.Value() = fChi2;
}
