#pragma once

#include "MACE/Core/DataModel/SimTrack/ICDCSimTrack.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::FloatBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;
using Utility::PhysicalConstant::electron_mass_c2;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class CDCHelixSimTrack;

class CDCPhysicsSimTrack : public CDCPhysicsTrack,
                           public ICDCSimTrack {
public:
    CDCPhysicsSimTrack() noexcept;
    CDCPhysicsSimTrack(const CDCPhysicsSimTrack&) noexcept = default;
    CDCPhysicsSimTrack(CDCPhysicsSimTrack&&) noexcept = default;
    virtual ~CDCPhysicsSimTrack() noexcept = default;
    CDCPhysicsSimTrack& operator=(const CDCPhysicsSimTrack&) noexcept = default;
    CDCPhysicsSimTrack& operator=(CDCPhysicsSimTrack&&) noexcept = default;

    explicit CDCPhysicsSimTrack(const CDCHelixSimTrack& helix, Double_t phiVertex = 0, Double_t B = 0.1_T, Double_t mass = electron_mass_c2);

    const auto& GetTrueVertexPosition() const { return fTrueVertexPosition; }
    const auto& GetTrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& GetTrueVertexMomentum() const { return fTrueVertexMomentum; }
    const auto& GetTrueParticle() const { return fTrueParticle; }

    template<typename A3Vector>
    void SetTrueVertexPosition(A3Vector&& pos) { fTrueVertexPosition = std::forward<A3Vector>(pos); }
    void SetTrueVertexPosition(Double_t x, Double_t y, Double_t z) { fTrueVertexPosition = {x, y, z}; }
    void SetTrueVertexEnergy(Double_t E) { fTrueVertexEnergy = E; }
    template<typename A3Vector>
    void SetTrueVertexMomentum(A3Vector&& mom) { fTrueVertexMomentum = std::forward<A3Vector>(mom); }
    void SetTrueVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fTrueVertexMomentum = {pX, pY, pZ}; }
    template<typename AString>
    void SetTrueParticle(AString&& particleName) { fTrueParticle = std::forward<AString>(particleName); }

    static consteval const char* BasicTreeName() noexcept { return "PhyTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Eigen::Vector3d fTrueVertexPosition;
    Double_t fTrueVertexEnergy;
    Eigen::Vector3d fTrueVertexMomentum;
    ShortString fTrueParticle;

    static Vector3FBranchSocket fgTrueVertexPosition;
    static FloatBranchSocket fgTrueVertexEnergy;
    static Vector3FBranchSocket fgTrueVertexMomentum;
    static ShortStringBranchSocket fgTrueParticle;
};

} // namespace MACE::Core::DataModel::Track
