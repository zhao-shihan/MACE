#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/Track/CDCTrackBase.hxx"
#include "MACE/DataModel/TransientData.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::inline Track {

using namespace LiteralUnit::MagneticFluxDensity;
using namespace std::string_view_literals;

using PhysicalConstant::electron_mass_c2;

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

    const auto& VertexPosition() const { return fVertexPosition; }
    template<Concept::NumericVector3D T>
    auto VertexPosition() const { return VectorCast<T>(fVertexPosition); }
    const auto& VertexEnergy() const { return fVertexEnergy; }
    const auto& VertexMomentum() const { return fVertexMomentum; }
    template<Concept::NumericVector3D T>
    auto VertexMomentum() const { return VectorCast<T>(fVertexMomentum); }
    const auto& Particle() const { return fParticle; }

    void VertexPosition(const stdx::array3d& x) { fVertexPosition = x; }
    void VertexPosition(auto&& x) { VectorAssign(fVertexPosition, std::forward<decltype(x)>(x)); }
    void VertexEnergy(double E) { fVertexEnergy = E; }
    void VertexMomentum(const stdx::array3d& p) { fVertexMomentum = p; }
    void VertexMomentum(auto&& p) { VectorAssign(fVertexMomentum, std::forward<decltype(p)>(p)); }
    void Particle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "PhyTrk"sv; }

private:
    stdx::array3d fVertexPosition;
    double fVertexEnergy;
    stdx::array3d fVertexMomentum;
    ShortString fParticle;

    static Vector3FBranchSocket fgVertexPosition;
    static FloatBranchSocket fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static ShortStringBranchSocket fgParticle;
};
static_assert(TransientData<CDCPhysicsTrack>);

} // namespace MACE::DataModel::inline Track
