#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/Vector2BranchSocket.hxx"
#include "Core/DataModel/BranchSocket/Vector3BranchSocket.hxx"
#include "Core/DataModel/DataFactory.hxx"
#include "Core/DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Vertex {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector2FBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MuoniumVertex : public ITransientData {
    friend DataFactory;

public:
    MuoniumVertex() noexcept;
    MuoniumVertex(const MuoniumVertex&) noexcept = default;
    MuoniumVertex(MuoniumVertex&&) noexcept = default;
    virtual ~MuoniumVertex() noexcept = default;
    MuoniumVertex& operator=(const MuoniumVertex&) noexcept = default;
    MuoniumVertex& operator=(MuoniumVertex&&) noexcept = default;

    [[nodiscard]] const auto& GetTCACDC() const { return fTCACDC; }
    [[nodiscard]] const auto& GetTCAMCP() const { return fTCAMCP; }
    [[nodiscard]] const auto& GetDeltaTCA() const { return fDeltaTCA; }
    [[nodiscard]] const auto& GetCPACDC() const { return fCPACDC; }
    [[nodiscard]] const auto& GetCPAMCP() const { return fCPAMCP; }
    [[nodiscard]] const auto& GetDCA() const { return fDCA; }
    [[nodiscard]] const auto& GetVertexEnergy() const { return fVertexEnergy; }
    [[nodiscard]] const auto& GetVertexMomentum() const { return fVertexMomentum; }
    [[nodiscard]] const auto& GetParticles() const { return fParticles; }

    void SetTCACDC(Double_t val) { fTCACDC = val; }
    void SetTCAMCP(Double_t val) { fTCAMCP = val; }
    void SetDeltaTCA(Double_t val) { fDeltaTCA = val; }
    template<typename Vector3_t>
    void SetCPACDC(Vector3_t&& pos) { fCPACDC = std::forward<Vector3_t>(pos); }
    void SetCPACDC(Double_t x, Double_t y, Double_t z) { fCPACDC.Set(x, y, z); }
    template<typename Vector2_t>
    void SetCPAMCP(Vector2_t&& pos) { fCPAMCP = std::forward<Vector2_t>(pos); }
    void SetCPAMCP(Double_t x, Double_t y) { fCPAMCP.Set(x, y); }
    void SetDCA(Double_t dca) { fDCA = dca; }
    void SetVertexEnergy(Double_t E) { fVertexEnergy = E; }
    template<typename Vector3_t>
    void SetVertexMomentum(Vector3_t&& mom) { fVertexMomentum = std::forward<Vector3_t>(mom); }
    void SetVertexMomentum(Double_t pX, Double_t pY, Double_t pZ) { fVertexMomentum.Set(pX, pY, pZ); }
    template<typename String_t>
    void SetParticles(String_t&& particleNames) { fParticles = std::forward<String_t>(particleNames); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "MVtx"; }

private:
    Double_t fTCACDC;
    Double_t fTCAMCP;
    Double_t fDeltaTCA;
    TEveVectorD fCPACDC;
    TEveVector2D fCPAMCP;
    Double_t fDCA;
    Double_t fVertexEnergy;
    TEveVectorD fVertexMomentum;
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

} // namespace MACE::Core::DataModel::Vertex
