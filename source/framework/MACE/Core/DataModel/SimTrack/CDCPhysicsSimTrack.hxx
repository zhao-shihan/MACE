#pragma once

#include "MACE/Core/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <string_view>
#include <utility>

namespace MACE::Core::DataModel::Track {

using namespace std::string_view_literals;
using namespace Utility::LiteralUnit::MagneticFluxDensity;
using Utility::PhysicalConstant::electron_mass_c2;

class CDCHelixSimTrack;

class CDCPhysicsSimTrack : public CDCPhysicsTrack,
                           public CDCSimTrackBase {
public:
    CDCPhysicsSimTrack() noexcept;
    virtual ~CDCPhysicsSimTrack() = default;

    CDCPhysicsSimTrack(const CDCPhysicsSimTrack&) noexcept = default;
    CDCPhysicsSimTrack(CDCPhysicsSimTrack&&) noexcept = default;
    CDCPhysicsSimTrack& operator=(const CDCPhysicsSimTrack&) noexcept = default;
    CDCPhysicsSimTrack& operator=(CDCPhysicsSimTrack&&) noexcept = default;

    explicit CDCPhysicsSimTrack(const CDCHelixSimTrack& helix, double phiVertex = 0, double B = 0.1_T, double mass = electron_mass_c2);

    const auto& GetTrueVertexPosition() const { return fTrueVertexPosition; }
    const auto& GetTrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& GetTrueVertexMomentum() const { return fTrueVertexMomentum; }
    const auto& GetTrueParticle() const { return fTrueParticle; }

    void SetTrueVertexPosition(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector3D(fTrueVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetTrueVertexEnergy(double E) { fTrueVertexEnergy = E; }
    void SetTrueVertexMomentum(auto&&... p) requires(sizeof...(p) > 0) { Utility::AssignVector3D(fTrueVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetTrueParticle(auto&& p) { fTrueParticle = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "PhyTrk"sv; }

private:
    Eigen::Vector3d fTrueVertexPosition;
    double fTrueVertexEnergy;
    Eigen::Vector3d fTrueVertexMomentum;
    Utility::ShortString fTrueParticle;

    static BranchSocket::Vector3FBranchSocket fgTrueVertexPosition;
    static BranchSocket::FloatBranchSocket fgTrueVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgTrueParticle;
};
static_assert(TransientData<CDCPhysicsSimTrack>);

} // namespace MACE::Core::DataModel::Track
