#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/Hit/CDCHit.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::inline SimHit {

class CDCSimHit : public CDCHit {
public:
    inline CDCSimHit() noexcept;
    virtual ~CDCSimHit() = default;

    CDCSimHit(const CDCSimHit& hit) noexcept = default;
    CDCSimHit(CDCSimHit&& hit) noexcept = default;
    CDCSimHit& operator=(const CDCSimHit& hit) noexcept = default;
    CDCSimHit& operator=(CDCSimHit&& hit) noexcept = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& Energy() const { return fEnergy; }
    const auto& Momentum() const { return fMomentum; }
    template<Concept::NumericVector3D T>
    auto Momentum() const { return VectorCast<T>(fMomentum); }
    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    template<Concept::NumericVector3D T>
    auto VertexPosition() const { return VectorCast<T>(fVertexPosition); }
    const auto& VertexEnergy() const { return fVertexEnergy; }
    const auto& VertexMomentum() const { return fVertexMomentum; }
    template<Concept::NumericVector3D T>
    auto VertexMomentum() const { return VectorCast<T>(fVertexMomentum); }
    const auto& Particle() const { return fParticle; }

    void G4EventID(int val) { fG4EventID = val; }
    void G4TrackID(int val) { fG4TrackID = val; }
    void Energy(double E) { fEnergy = E; }
    void Momentum(const stdx::array3d& p) { fMomentum = p; }
    void Momentum(auto&& p) { VectorAssign(fMomentum, std::forward<decltype(p)>(p)); }
    void VertexTime(double val) { fVertexTime = val; }
    void VertexPosition(const stdx::array3d& x) { fVertexPosition = x; }
    void VertexPosition(auto&& x) { VectorAssign(fVertexPosition, std::forward<decltype(x)>(x)); }
    void VertexEnergy(double E) { fVertexEnergy = E; }
    void VertexMomentum(const stdx::array3d& p) { fVertexMomentum = p; }
    void VertexMomentum(auto&& p) { VectorAssign(fVertexMomentum, std::forward<decltype(p)>(p)); }
    void Particle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("CDCSimHit"); }

private:
    int fG4EventID;
    int fG4TrackID;
    double fEnergy;
    stdx::array3d fMomentum;
    double fVertexTime;
    stdx::array3d fVertexPosition;
    double fVertexEnergy;
    stdx::array3d fVertexMomentum;
    ShortString fParticle;

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
static_assert(TransientData<CDCSimHit>);

} // namespace MACE::DataModel::inline SimHit

#include "MACE/DataModel/SimHit/CDCSimHit.inl"
