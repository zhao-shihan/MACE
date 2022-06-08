#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Track/ICDCTrack.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

namespace MACE::Core::DataModel::Track {

using BranchSocket::FloatBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;
using Utility::PhysicalConstant::electron_mass_c2;
using namespace Utility::LiteralUnit::MagneticFluxDensity;

class CDCHelixTrack;

class CDCPhysicsTrack : public ICDCTrack {
public:
    CDCPhysicsTrack() noexcept;
    CDCPhysicsTrack(const CDCPhysicsTrack&) noexcept = default;
    CDCPhysicsTrack(CDCPhysicsTrack&&) noexcept = default;
    virtual ~CDCPhysicsTrack() noexcept = default;
    CDCPhysicsTrack& operator=(const CDCPhysicsTrack&) noexcept = default;
    CDCPhysicsTrack& operator=(CDCPhysicsTrack&&) noexcept = default;

    explicit CDCPhysicsTrack(const CDCHelixTrack& helix, Double_t phiVertex = 0, Double_t B = 0.1_T, Double_t mass = electron_mass_c2);

    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetVertexEnergy() const { return fVertexEnergy; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticle() const { return fParticle; }

    template<typename Vector3T>
    void SetVertexPosition(Vector3T&& pos) { fVertexPosition = std::forward<Vector3T>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3T>
    void SetVertexMomentum(Vector3T&& mom) { fVertexMomentum = std::forward<Vector3T>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum = {pX, pY, pZ}; }
    template<typename StringT>
    void SetParticle(StringT&& particleName) { fParticle = std::forward<StringT>(particleName); }

    static consteval const char* BasicTreeName() noexcept { return "PhyTrk"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Eigen::Vector3d fVertexPosition;
    Double_t fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
    ShortString fParticle;

    static Vector3FBranchSocket fgVertexPosition;
    static FloatBranchSocket fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static ShortStringBranchSocket fgParticle;
};

} // namespace MACE::Core::DataModel::Track
