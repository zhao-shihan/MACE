#pragma once

#include "MACE/Core/DataFactory.hxx"
#include "MACE/Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/ReconMuonium/MuoniumVertex.hxx"

namespace MACE::ReconMuonium {

using Core::DataModel::BranchSocket::DoubleBranchSocket;
using Core::DataModel::BranchSocket::FloatBranchSocket;
using Core::DataModel::BranchSocket::ShortStringBranchSocket;
using Core::DataModel::BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MuoniumSimVertex : public MuoniumVertex {
public:
    MuoniumSimVertex() noexcept;
    MuoniumSimVertex(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex(MuoniumSimVertex&&) noexcept = default;
    virtual ~MuoniumSimVertex() noexcept = default;
    MuoniumSimVertex& operator=(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex& operator=(MuoniumSimVertex&&) noexcept = default;

    const auto& GetTrueVertexTime() const { return fTrueVertexTime; }
    const auto& GetTrueVertexPosition() const { return fTrueVertexPosition; }
    const auto& GetTrueVertexEnergy() const { return fTrueVertexEnergy; }
    const auto& GetTrueVertexMomentum() const { return fTrueVertexMomentum; }
    const auto& GetTrueParticles() const { return fTrueParticles; }

    void SetTrueVertexTime(Double_t val) { fTrueVertexTime = val; }
    template<typename Vector3T>
    void SetTrueVertexPosition(Vector3T&& pos) { fTrueVertexPosition = std::forward<Vector3T>(pos); }
    void SetTrueVertexPosition(Double_t x, Double_t y, Double_t z) { fTrueVertexPosition = {x, y, z}; }
    void SetTrueVertexEnergy(Double_t val) { fTrueVertexEnergy = val; }
    template<typename Vector3T>
    void SetTrueVertexMomentum(Vector3T&& pos) { fTrueVertexMomentum = std::forward<Vector3T>(pos); }
    void SetTrueVertexMomentum(Double_t x, Double_t y, Double_t z) { fTrueVertexMomentum = {x, y, z}; }
    template<typename StringT>
    void SetTrueParticles(StringT&& particleNames) { fTrueParticles = std::forward<StringT>(particleNames); }

    static consteval const char* BasicTreeName() noexcept { return "MVtx"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fTrueVertexTime;
    Eigen::Vector3d fTrueVertexPosition;
    Double_t fTrueVertexEnergy;
    Eigen::Vector3d fTrueVertexMomentum;
    ShortString fTrueParticles;

    static DoubleBranchSocket fgTrueVertexTime;
    static Vector3FBranchSocket fgTrueVertexPosition;
    static FloatBranchSocket fgTrueVertexEnergy;
    static Vector3FBranchSocket fgTrueVertexMomentum;
    static ShortStringBranchSocket fgTrueParticles;
};

} // namespace MACE::ReconMuonium
