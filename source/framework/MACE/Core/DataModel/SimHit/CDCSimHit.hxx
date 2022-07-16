#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/CDCHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class CDCSimHit : public Hit::CDCHit {
public:
    CDCSimHit() noexcept;
    CDCSimHit(const CDCSimHit& hit) noexcept = default;
    CDCSimHit(CDCSimHit&& hit) noexcept = default;
    virtual ~CDCSimHit() noexcept = default;
    CDCSimHit& operator=(const CDCSimHit& hit) noexcept = default;
    CDCSimHit& operator=(CDCSimHit&& hit) noexcept = default;

    const auto& GetEnergy() const { return fEnergy; }
    const auto& GetMomentum() const { return fMomentum; }
    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetVertexEnergy() const { return fVertexEnergy; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetEnergy(Double_t E) { fEnergy = E; }
    template<typename Vector3T>
    void SetMomentum(Vector3T&& mom) { fMomentum = std::forward<Vector3T>(mom); }
    void SetMomentum(Double_t pX, Double_t pY, Double_t pZ) { fMomentum = {pX, pY, pZ}; }
    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3T>
    void SetVertexPosition(Vector3T&& pos) { fVertexPosition = std::forward<Vector3T>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3T>
    void SetVertexMomentum(Vector3T&& mom) { fVertexMomentum = std::forward<Vector3T>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum = {pX, pY, pZ}; }
    template<typename StringT>
    void SetParticle(StringT&& particleName) { fParticle = std::forward<StringT>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

    static consteval const char* BasicTreeName() noexcept { return "CDCSimHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fEnergy;
    Eigen::Vector3d fMomentum;
    Double_t fVertexTime;
    Eigen::Vector3d fVertexPosition;
    Double_t fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
    ShortString fParticle;
    Int_t fG4EventID;
    Int_t fG4TrackID;

    static FloatBranchSocket fgEnergy;
    static Vector3FBranchSocket fgMomentum;
    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static FloatBranchSocket fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
};

} // namespace MACE::Core::DataModel::SimHit
