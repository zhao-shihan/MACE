#pragma once

#include "DataModel/Interface/Transient.hxx"
#include "DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector3BranchSocket.hxx"

class MACE::DataModel::MuoniumVertex :
    public MACE::DataModel::Interface::Transient {
    using Base = MACE::DataModel::Interface::Transient;
    friend MACE::DataModel::DataHub;

public:
    MuoniumVertex() noexcept;
    MuoniumVertex(const MuoniumVertex&) noexcept = default;
    MuoniumVertex(MuoniumVertex&&) noexcept = default;
    virtual ~MuoniumVertex() noexcept = default;
    MuoniumVertex& operator=(const MuoniumVertex&) noexcept = default;
    MuoniumVertex& operator=(MuoniumVertex&&) noexcept = default;

    MuoniumVertex(const HelixTrack& helix, Double_t B, Double_t mass);

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
    Double_t    fVertexTimeCDC;
    TEveVectorD fVertexPositionCDC;
    Double_t    fVertexTimeMCP;
    TEveVectorD fVertexPositionMCP;

    static ShortStringBranchSocket fgParticleName;
    static DoubleBranchSocket      fgVertexTimeCDC;
    static Vector3FBranchSocket    fgVertexPositionCDC;
    static DoubleBranchSocket      fgVertexTimeMCP;
    static Vector3FBranchSocket    fgVertexPositionMCP;
};

inline void MACE::DataModel::MuoniumVertex::FillBranchSockets() const noexcept {
    Base::FillBranchSockets();
    fgVertexTimeCDC.SetValue(fVertexTimeCDC);
    fgVertexPositionCDC.SetValue(fVertexPositionCDC);
    fgVertexTimeMCP.SetValue(fVertexTimeMCP);
    fgVertexPositionMCP.SetValue(fVertexPositionMCP);
    fgParticleName.SetValue(fParticleName);
}
