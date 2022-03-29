#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/Track/ICDCTrack.hxx"
#include "Utility/LiteralUnit.hxx"
#include "Utility/PhysicalConstant.hxx"

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

    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3_t>
    void SetVertexMomentum(Vector3_t&& mom) { fVertexMomentum = std::forward<Vector3_t>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum = {pX, pY, pZ}; }
    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }

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
