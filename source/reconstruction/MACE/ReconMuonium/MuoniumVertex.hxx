#pragma once

#include "MACE/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/DataModel/DataFactory.hxx"
#include "MACE/Extension/stdx/array_alias.hxx"
#include "MACE/Utility/VectorAssign.hxx"

#include <array>
#include <string_view>
#include <utility>

namespace MACE::ReconMuonium {

namespace BranchSocket = Core::DataModel::inline BranchSocket;
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
    void SetCPACDC(auto&& x) { VectorAssign(fCPACDC, std::forward<decltype(x)>(x)); }
    void SetCPAMCP(auto&& x) { VectorAssign(fCPAMCP, std::forward<decltype(x)>(x)); }
    void SetDCA(double dca) { fDCA = dca; }
    void VertexEnergy(double E) { fVertexEnergy = E; }
    void VertexMomentum(auto&& p) { VectorAssign(fVertexMomentum, std::forward<decltype(p)>(p)); }
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
    ShortString fParticles;

    static DoubleBranchSocket fgTCACDC;
    static DoubleBranchSocket fgTCAMCP;
    static DoubleBranchSocket fgDeltaTCA;
    static Vector3FBranchSocket fgCPACDC;
    static Vector2FBranchSocket fgCPAMCP;
    static FloatBranchSocket fgDCA;
    static FloatBranchSocket fgVertexEnergy;
    static Vector3FBranchSocket fgVertexMomentum;
    static ShortStringBranchSocket fgParticles;
};
static_assert(Core::DataModel::TransientData<MuoniumVertex>);

} // namespace MACE::ReconMuonium
