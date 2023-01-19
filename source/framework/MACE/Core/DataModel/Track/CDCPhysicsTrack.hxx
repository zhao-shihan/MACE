#pragma once

#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/Core/DataModel/TransientData.hxx"
#include "MACE/Utility/AssignVector.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Track {

using namespace Utility::LiteralUnit::MagneticFluxDensity;
using Utility::ShortString;
using Utility::PhysicalConstant::electron_mass_c2;

class CDCHelixTrack;

class CDCPhysicsTrack : public CDCTrackBase {
public:
    CDCPhysicsTrack() noexcept;
    virtual ~CDCPhysicsTrack() = default;

    CDCPhysicsTrack(const CDCPhysicsTrack&) noexcept = default;
    CDCPhysicsTrack(CDCPhysicsTrack&&) noexcept = default;
    CDCPhysicsTrack& operator=(const CDCPhysicsTrack&) noexcept = default;
    CDCPhysicsTrack& operator=(CDCPhysicsTrack&&) noexcept = default;

    explicit CDCPhysicsTrack(const CDCHelixTrack& helix, double phiVertex = 0, double B = 0.1_T, double mass = electron_mass_c2);

    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetVertexEnergy() const { return fVertexEnergy; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticle() const { return fParticle; }

    void SetVertexPosition(auto&&... x)
        requires(sizeof...(x) > 0)
    { Utility::AssignVector3D(fVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetVertexEnergy(double E) { fVertexEnergy = E; }
    void SetVertexMomentum(auto&&... p)
        requires(sizeof...(p) > 0)
    { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetParticle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "PhyTrk"sv; }

private:
    Eigen::Vector3d fVertexPosition;
    double fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
    ShortString fParticle;

    static BranchSocket::Vector3FBranchSocket fgVertexPosition;
    static BranchSocket::FloatBranchSocket fgVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgParticle;
};
static_assert(TransientData<CDCPhysicsTrack>);

} // namespace MACE::Core::DataModel::Track
