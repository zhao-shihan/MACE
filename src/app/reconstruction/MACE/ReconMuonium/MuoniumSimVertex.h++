#pragma once

#include "Mustard/Concept/NumericVector.h++"
#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.h++"
#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.h++"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.h++"
#include "MACE/DataModel/DataFactory.h++"
#include "MACE/ReconMuonium/MuoniumVertex.h++"
#include "Mustard/Utility/VectorAssign.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "muc/array"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::ReconMuonium {

namespace BranchSocket = Core::DataModel::inline BranchSocket;
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
    void TrueVertexPosition(const muc::array3d& x) { fTrueVertexPosition = x; }
    void TrueVertexPosition(auto&& x) { fTrueVertexPosition <<= std::forward<decltype(x)>(x); }
    void TrueVertexEnergy(double val) { fTrueVertexEnergy = val; }
    void TrueVertexMomentum(const muc::array3d& p) { fTrueVertexMomentum = p; }
    void TrueVertexMomentum(auto&& p) { fTrueVertexMomentum <<= std::forward<decltype(p)>(p); }
    void TrueParticles(auto&& p) { fTrueParticles = std::forward<decltype(p)>(p); }

    void FillAllBranchSocket() const& noexcept;
    static void CreateAllBranch(TTree& tree);
    static void ConnectToAllBranch(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MVtx"sv; }

private:
    double fTrueVertexTime;
    muc::array3d fTrueVertexPosition;
    double fTrueVertexEnergy;
    muc::array3d fTrueVertexMomentum;
    String15 fTrueParticles;

    static DoubleBranchSocket fgTrueVertexTime;
    static Vector3FBranchSocket fgTrueVertexPosition;
    static FloatBranchSocket fgTrueVertexEnergy;
    static Vector3FBranchSocket fgTrueVertexMomentum;
    static ShortStringBranchSocket fgTrueParticles;
};
static_assert(Core::DataModel::TransientData<MuoniumSimVertex>);

} // namespace MACE::ReconMuonium
