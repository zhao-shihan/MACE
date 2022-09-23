#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Utility/AssignVector.hxx"

#include <string_view>
#include <utility>

namespace MACE::ReconMuonium {

namespace BranchSocket = Core::DataModel::BranchSocket;
using namespace std::string_view_literals;

class MuoniumVertex {
public:
    MuoniumVertex() noexcept;
    virtual ~MuoniumVertex() = default;

    MuoniumVertex(const MuoniumVertex&) noexcept = default;
    MuoniumVertex(MuoniumVertex&&) noexcept = default;
    MuoniumVertex& operator=(const MuoniumVertex&) noexcept = default;
    MuoniumVertex& operator=(MuoniumVertex&&) noexcept = default;

    const auto& GetTCACDC() const { return fTCACDC; }
    const auto& GetTCAMCP() const { return fTCAMCP; }
    const auto& GetDeltaTCA() const { return fDeltaTCA; }
    const auto& GetCPACDC() const { return fCPACDC; }
    const auto& GetCPAMCP() const { return fCPAMCP; }
    const auto& GetDCA() const { return fDCA; }
    const auto& GetVertexEnergy() const { return fVertexEnergy; }
    const auto& GetVertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticles() const { return fParticles; }

    void SetTCACDC(double val) { fTCACDC = val; }
    void SetTCAMCP(double val) { fTCAMCP = val; }
    void SetDeltaTCA(double val) { fDeltaTCA = val; }
    void SetCPACDC(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector3D(fCPACDC, std::forward<decltype(x)>(x)...); }
    void SetCPAMCP(auto&&... x) requires(sizeof...(x) > 0) { Utility::AssignVector2D(fCPAMCP, std::forward<decltype(x)>(x)...); }
    void SetDCA(double dca) { fDCA = dca; }
    void SetVertexEnergy(double E) { fVertexEnergy = E; }
    void SetVertexMomentum(auto&&... p) requires(sizeof...(p) > 0) { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetParticles(auto&& p) { fParticles = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MVtx"sv; }

private:
    double fTCACDC;
    double fTCAMCP;
    double fDeltaTCA;
    Eigen::Vector3d fCPACDC;
    Eigen::Vector2d fCPAMCP;
    double fDCA;
    double fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
    Utility::ShortString fParticles;

    static BranchSocket::DoubleBranchSocket fgTCACDC;
    static BranchSocket::DoubleBranchSocket fgTCAMCP;
    static BranchSocket::DoubleBranchSocket fgDeltaTCA;
    static BranchSocket::Vector3FBranchSocket fgCPACDC;
    static BranchSocket::Vector2FBranchSocket fgCPAMCP;
    static BranchSocket::FloatBranchSocket fgDCA;
    static BranchSocket::FloatBranchSocket fgVertexEnergy;
    static BranchSocket::Vector3FBranchSocket fgVertexMomentum;
    static BranchSocket::ShortStringBranchSocket fgParticles;
};
static_assert(Core::DataModel::TransientData<MuoniumVertex>);

} // namespace MACE::ReconMuonium
