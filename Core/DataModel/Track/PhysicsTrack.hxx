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

    PhysicsTrack(const HelixTrack& helix, UInt_t absQ, Double_t B, Double_t mass);

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetVertexEnergy() const { return fVertexEnergy; }
    [[nodiscard]] const auto& GetVertexMomentum() const { return fVertexMomentum; }
    [[nodiscard]] const auto& GetCharge() const { return fCharge; }
    [[nodiscard]] const auto& GetNumberOfFittedPoints() const { return fNumberOfFittedPoints; }
    [[nodiscard]] const auto& GetChi2() const { return fChi2; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    void SetVertexPosition(const TEveVectorD& pos) { fVertexPosition = pos; }
    void SetVertexPosition(TEveVectorD&& pos) { fVertexPosition = std::move(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    void SetVertexMomentum(const TEveVectorD& mom) { fVertexMomentum = mom; }
    void SetVertexMomentum(TEveVectorD&& mom) { fVertexMomentum = std::move(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum.Set(pX, pY, pZ); }
    void SetCharge(Int_t q) { fCharge = q; }
    void SetNumberOfFittedPoints(Int_t n) { fNumberOfFittedPoints = n; }
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
    Double_t    fVertexEnergy;
    TEveVectorD fVertexMomentum;
    Int_t       fCharge;
    Int_t       fNumberOfFittedPoints;
    Double_t    fChi2;

    static DoubleBranchSocket   fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static FloatBranchSocket    fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static IntBranchSocket      fgCharge;
    static IntBranchSocket      fgNumberOfFittedPoints;
    static FloatBranchSocket    fgChi2;
};

inline void MACE::DataModel::PhysicsTrack::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgVertexTime.Value() = fVertexTime;
    fgVertexPosition.Value() = fVertexPosition;
    fgVertexEnergy.Value() = fVertexEnergy;
    fgVertexMomentum.Value() = fVertexMomentum;
    fgCharge.Value() = fCharge;
    fgNumberOfFittedPoints.Value() = fNumberOfFittedPoints;
    fgChi2.Value() = fChi2;
}
