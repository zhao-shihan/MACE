#pragma once

#include "DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector3BranchSocket.hxx"
#include "DataModel/DataHub.hxx"
#include "DataModel/ITransientData.hxx"

namespace MACE::Core::DataModel::Vertex {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MuoniumVertex : public ITransientData {
    friend DataHub;

public:
    MuoniumVertex() noexcept;
    MuoniumVertex(const MuoniumVertex&) noexcept = default;
    MuoniumVertex(MuoniumVertex&&) noexcept = default;
    virtual ~MuoniumVertex() noexcept = default;
    MuoniumVertex& operator=(const MuoniumVertex&) noexcept = default;
    MuoniumVertex& operator=(MuoniumVertex&&) noexcept = default;

    [[nodiscard]] const auto& GetParticleName() const { return fParticleName; }
    [[nodiscard]] const auto& GetVertexTimeCDC() const { return fVertexTimeCDC; }
    [[nodiscard]] const auto& GetVertexPositionCDC() const { return fVertexPositionCDC; }
    [[nodiscard]] const auto& GetVertexTimeMCP() const { return fVertexTimeMCP; }
    [[nodiscard]] const auto& GetVertexPositionMCP() const { return fVertexPositionMCP; }

    template<typename String_t>
    void SetParticleName(String_t&& particleName) { fParticleName = std::forward<String_t>(particleName); }
    void SetVertexTimeCDC(Double_t val) { fVertexTimeCDC = val; }
    template<typename Vector3_t>
    void SetVertexPositionCDC(Vector3_t&& pos) { fVertexPositionCDC = std::forward<Vector3_t>(pos); }
    void SetVertexPositionCDC(Double_t x, Double_t y, Double_t z) { fVertexPositionCDC.Set(x, y, z); }
    void SetVertexTimeMCP(Double_t val) { fVertexTimeMCP = val; }
    template<typename Vector3_t>
    void SetVertexPositionMCP(Vector3_t&& pos) { fVertexPositionMCP = std::forward<Vector3_t>(pos); }
    void SetVertexPositionMCP(Double_t x, Double_t y, Double_t z) { fVertexPositionMCP.Set(x, y, z); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "MVtx"; }

private:
    ShortString fParticleName;
    Double_t fVertexTimeCDC;
    TEveVectorD fVertexPositionCDC;
    Double_t fVertexTimeMCP;
    TEveVectorD fVertexPositionMCP;

    static ShortStringBranchSocket fgParticleName;
    static DoubleBranchSocket fgVertexTimeCDC;
    static Vector3FBranchSocket fgVertexPositionCDC;
    static DoubleBranchSocket fgVertexTimeMCP;
    static Vector3FBranchSocket fgVertexPositionMCP;
};

inline void MuoniumVertex::FillBranchSockets() const noexcept {
    ITransientData::FillBranchSockets();
    fgVertexTimeCDC.SetValue(fVertexTimeCDC);
    fgVertexPositionCDC.SetValue(fVertexPositionCDC);
    fgVertexTimeMCP.SetValue(fVertexTimeMCP);
    fgVertexPositionMCP.SetValue(fVertexPositionMCP);
    fgParticleName.SetValue(fParticleName);
}

} // namespace MACE::Core::DataModel::Vertex
