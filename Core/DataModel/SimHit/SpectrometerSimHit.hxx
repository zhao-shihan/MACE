#pragma once

#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/Hit/SpectrometerHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class SpectrometerSimHit : public Hit::SpectrometerHit {
    friend DataFactory;

public:
    SpectrometerSimHit() noexcept;
    SpectrometerSimHit(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit(SpectrometerSimHit&& hit) noexcept = default;
    virtual ~SpectrometerSimHit() noexcept = default;
    SpectrometerSimHit& operator=(const SpectrometerSimHit& hit) noexcept = default;
    SpectrometerSimHit& operator=(SpectrometerSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetEnergy() const { return fEnergy; }
    [[nodiscard]] const auto& GetMomentum() const { return fMomentum; }
    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetVertexEnergy() const { return fVertexEnergy; }
    [[nodiscard]] const auto& GetVertexMomentum() const { return fVertexMomentum; }
    [[nodiscard]] const auto& GetParticle() const { return fParticle; }
    [[nodiscard]] const auto& GetG4EventID() const { return fG4EventID; }
    [[nodiscard]] const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetEnergy(Double_t E) { fEnergy = E; }
    template<typename Vector3_t>
    void SetMomentum(Vector3_t&& mom) { fMomentum = std::forward<Vector3_t>(mom); }
    void SetMomentum(Double_t pX, Double_t pY, Double_t pZ) { fMomentum = {pX, pY, pZ}; }
    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3_t>
    void SetVertexMomentum(Vector3_t&& mom) { fVertexMomentum = std::forward<Vector3_t>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum = {pX, pY, pZ}; }
    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CDCSimHit"; }

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
