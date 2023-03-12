#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Core/DataModel/SimTrack/CDCSimTrackBase.hxx"
#include "MACE/Core/DataModel/Track/CDCPhysicsTrack.hxx"
#include "MACE/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <array>
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

    const auto& TrueVertexPosition() const { return fTrueVertexPosition; }
    template<Concept::NumericVector3D T>
    auto TrueVertexPosition() const { return Utility::VectorCast<T>(fTrueVertexPosition); }
    const auto& TrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& TrueVertexMomentum() const { return fTrueVertexMomentum; }
    template<Concept::NumericVector3D T>
    auto TrueVertexMomentum() const { return Utility::VectorCast<T>(fTrueVertexMomentum); }
    const auto& GetTrueParticle() const { return fTrueParticle; }

    void TrueVertexPosition(const stdx::array3d& x) { fTrueVertexPosition = x; }
    void TrueVertexPosition(auto&& x) { Utility::VectorAssign(fTrueVertexPosition, std::forward<decltype(x)>(x)); }
    void TrueVertexEnergy(double E) { fTrueVertexEnergy = E; }
    void TrueVertexMomentum(const stdx::array3d& p) { fTrueVertexMomentum = p; }
    void TrueVertexMomentum(auto&& p) { Utility::VectorAssign(fTrueVertexMomentum, std::forward<decltype(p)>(p)); }
    void SetTrueParticle(auto&& p) { fTrueParticle = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "PhyTrk"sv; }

private:
    stdx::array3d fTrueVertexPosition;
    double fTrueVertexEnergy;
    stdx::array3d fTrueVertexMomentum;
    Utility::ShortString fTrueParticle;

    static BranchSocket::Vector3FBranchSocket fgTrueVertexPosition;
    static BranchSocket::FloatBranchSocket fgTrueVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgTrueParticle;
};
static_assert(TransientData<CDCPhysicsSimTrack>);

} // namespace MACE::Core::DataModel::Track
