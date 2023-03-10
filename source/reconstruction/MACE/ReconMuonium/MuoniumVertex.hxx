#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Utility/AssignVector.hxx"
#include "MACE/stdx/array_alias.hxx"

#include <array>
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
    const auto& VertexEnergy() const { return fVertexEnergy; }
    const auto& VertexMomentum() const { return fVertexMomentum; }
    const auto& GetParticles() const { return fParticles; }

    void SetTCACDC(double val) { fTCACDC = val; }
    void SetTCAMCP(double val) { fTCAMCP = val; }
    void SetDeltaTCA(double val) { fDeltaTCA = val; }
    void SetCPACDC(auto&&... x)
        requires(sizeof...(x) >= 1)
    { Utility::AssignVector3D(fCPACDC, std::forward<decltype(x)>(x)...); }
    void SetCPAMCP(auto&&... x)
        requires(sizeof...(x) >= 1)
    { Utility::AssignVector2D(fCPAMCP, std::forward<decltype(x)>(x)...); }
    void SetDCA(double dca) { fDCA = dca; }
    void VertexEnergy(double E) { fVertexEnergy = E; }
    void VertexMomentum(auto&&... p)
        requires(sizeof...(p) >= 1)
    { Utility::AssignVector3D(fVertexMomentum, std::forward<decltype(p)>(p)...); }
    void SetParticles(auto&& p) { fParticles = std::forward<decltype(p)>(p); }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MVtx"sv; }

private:
    double fTCACDC;
    double fTCAMCP;
    double fDeltaTCA;
    stdx::array3d fCPACDC;
    stdx::array2d fCPAMCP;
    double fDCA;
    double fVertexEnergy;
    stdx::array3d fVertexMomentum;
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
