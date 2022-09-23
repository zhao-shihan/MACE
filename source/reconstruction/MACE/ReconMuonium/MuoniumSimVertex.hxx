#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/ReconMuonium/MuoniumVertex.hxx"
#include "MACE/Utility/AssignVector.hxx"

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

    const auto& GetTrueVertexTime() const { return fTrueVertexTime; }
    const auto& GetTrueVertexPosition() const { return fTrueVertexPosition; }
    const auto& GetTrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& GetTrueVertexMomentum() const { return fTrueVertexMomentum; }
    const auto& GetTrueParticles() const { return fTrueParticles; }

    void SetTrueVertexTime(double val) { fTrueVertexTime = val; }
    void SetTrueVertexPosition(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector3D(fTrueVertexPosition, std::forward<decltype(x)>(x)...); }
    void SetTrueVertexEnergy(double val) { fTrueVertexEnergy = val; }
    void SetTrueVertexMomentum(auto&&... p) requires(sizeof...(p) > 0) { Utility::AssignVector3D(fTrueVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetTrueParticles(auto&& p) { fTrueParticles = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MVtx"sv; }

private:
    double fTrueVertexTime;
    Eigen::Vector3d fTrueVertexPosition;
    double fTrueVertexEnergy;
    Eigen::Vector3d fTrueVertexMomentum;
    Utility::ShortString fTrueParticles;

    static BranchSocket::DoubleBranchSocket fgTrueVertexTime;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexPosition;
    static BranchSocket::FloatBranchSocket fgTrueVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgTrueVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgTrueParticles;
};
static_assert(Core::DataModel::TransientData<MuoniumSimVertex>);

} // namespace MACE::ReconMuonium
