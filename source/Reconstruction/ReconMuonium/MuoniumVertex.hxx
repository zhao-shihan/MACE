#pragma once

#include "Core/DataFactory.hxx"
#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Reconstruction::ReconMuonium {

using Core::DataModel::BranchSocket::DoubleBranchSocket;
using Core::DataModel::BranchSocket::FloatBranchSocket;
using Core::DataModel::BranchSocket::ShortStringBranchSocket;
using Core::DataModel::BranchSocket::Vector2FBranchSocket;
using Core::DataModel::BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MuoniumVertex : public Core::DataModel::ITransientData {
public:
    MuoniumVertex() noexcept;
    MuoniumVertex(const MuoniumVertex&) noexcept = default;
    MuoniumVertex(MuoniumVertex&&) noexcept = default;
    virtual ~MuoniumVertex() noexcept = default;
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

    void SetTCACDC(Double_t val) { fTCACDC = val; }
    void SetTCAMCP(Double_t val) { fTCAMCP = val; }
    void SetDeltaTCA(Double_t val) { fDeltaTCA = val; }
    template<typename Vector3_t>
    void SetCPACDC(Vector3_t&& pos) { fCPACDC = std::forward<Vector3_t>(pos); }
    void SetCPACDC(Double_t x, Double_t y, Double_t z) { fCPACDC = {x, y, z}; }
    template<typename Vector2_t>
    void SetCPAMCP(Vector2_t&& pos) { fCPAMCP = std::forward<Vector2_t>(pos); }
    void SetCPAMCP(Double_t x, Double_t y) { fCPAMCP = {x, y}; }
    void SetDCA(Double_t dca) { fDCA = dca; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3_t>
    void SetVertexMomentum(Vector3_t&& mom) { fVertexMomentum = std::forward<Vector3_t>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum = {pX, pY, pZ}; }
    template<typename String_t>
    void SetParticles(String_t&& particleNames) { fParticles = std::forward<String_t>(particleNames); }

    static consteval const char* BasicTreeName() noexcept { return "MVtx"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fTCACDC;
    Double_t fTCAMCP;
    Double_t fDeltaTCA;
    Eigen::Vector3d fCPACDC;
    Eigen::Vector2d fCPAMCP;
    Double_t fDCA;
    Double_t fVertexEnergy;
    Eigen::Vector3d fVertexMomentum;
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

} // namespace MACE::Reconstruction::ReconMuonium
