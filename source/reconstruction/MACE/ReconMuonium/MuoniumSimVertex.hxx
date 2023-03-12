#pragma once

#include "MACE/Concept/NumericVector.hxx"
#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/ReconMuonium/MuoniumVertex.hxx"
#include "MACE/Utility/VectorAssign.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::ReconMuonium {

namespace BranchSocket = Core::DataModel::BranchSocket;
using namespace std::string_view_literals;

class MuoniumSimVertex : public MuoniumVertex {
public:
    MuoniumSimVertex() noexcept;
    virtual ~MuoniumSimVertex() = default;

    MuoniumSimVertex(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex(MuoniumSimVertex&&) noexcept = default;
    MuoniumSimVertex& operator=(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex& operator=(MuoniumSimVertex&&) noexcept = default;

    const auto& TrueVertexTime() const { return fTrueVertexTime; }
    const auto& TrueVertexPosition() const { return fTrueVertexPosition; }
    const auto& TrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& TrueVertexMomentum() const { return fTrueVertexMomentum; }
    const auto& TrueParticles() const { return fTrueParticles; }

    void TrueVertexTime(double val) { fTrueVertexTime = val; }
    void TrueVertexPosition(const stdx::array3d& x) { fTrueVertexPosition = x; }
    void TrueVertexPosition(auto&& x) { VectorAssign(fTrueVertexPosition, std::forward<decltype(x)>(x)); }
    void TrueVertexEnergy(double val) { fTrueVertexEnergy = val; }
    void TrueVertexMomentum(const stdx::array3d& p) { fTrueVertexMomentum = p; }
    void TrueVertexMomentum(auto&& p) { VectorAssign(fTrueVertexMomentum, std::forward<decltype(p)>(p)); }
    void TrueParticles(auto&& p) { fTrueParticles = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MVtx"sv; }

private:
    double fTrueVertexTime;
    stdx::array3d fTrueVertexPosition;
    double fTrueVertexEnergy;
    stdx::array3d fTrueVertexMomentum;
    ShortString fTrueParticles;

    static BranchSocket::DoubleBranchSocket fgTrueVertexTime;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexPosition;
    static BranchSocket::FloatBranchSocket fgTrueVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgTrueParticles;
};
static_assert(Core::DataModel::TransientData<MuoniumSimVertex>);

} // namespace MACE::ReconMuonium
