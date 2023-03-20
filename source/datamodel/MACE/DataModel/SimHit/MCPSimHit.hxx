#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/Hit/MCPHit.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::DataModel::inline SimHit {

class MCPSimHit : public MCPHit {
public:
    inline MCPSimHit() noexcept;
    virtual ~MCPSimHit() noexcept = default;

    MCPSimHit(const MCPSimHit& hit) noexcept = default;
    MCPSimHit(MCPSimHit&& hit) noexcept = default;
    MCPSimHit& operator=(const MCPSimHit& hit) noexcept = default;
    MCPSimHit& operator=(MCPSimHit&& hit) noexcept = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& VertexTime() const { return fVertexTime; }
    const auto& VertexPosition() const { return fVertexPosition; }
    template<Concept::NumericVector3D T>
    auto VertexPosition() const { return VectorCast<T>(fVertexPosition); }
    const auto& Particle() const { return fParticle; }

    void G4EventID(int val) { fG4EventID = val; }
    void G4TrackID(int val) { fG4TrackID = val; }
    void VertexTime(double val) { fVertexTime = val; }
    void VertexPosition(const stdx::array3d& x) { fVertexPosition = x; }
    void VertexPosition(auto&& x) { VectorAssign(fVertexPosition, std::forward<decltype(x)>(x)); }
    void Particle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("MCPSimHit"); }

private:
    int fG4EventID;
    int fG4TrackID;
    double fVertexTime;
    stdx::array3d fVertexPosition;
    ShortString fParticle;

    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static ShortStringBranchSocket fgParticle;
};
static_assert(TransientData<MCPSimHit>);

} // namespace MACE::DataModel::inline SimHit

#include "MACE/DataModel/SimHit/MCPSimHit.inl"
