#pragma once

#include "Core/DataModel/BranchSocket/FundamentalBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "Core/DataModel/DataFactory.hxx"
#include "Core/DataModel/Vertex/MuoniumVertex.hxx"

namespace MACE::Core::DataModel::SimVertex {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::FloatBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MuoniumSimVertex : public Vertex::MuoniumVertex {
    friend DataFactory;

public:
    MuoniumSimVertex() noexcept;
    MuoniumSimVertex(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex(MuoniumSimVertex&&) noexcept = default;
    virtual ~MuoniumSimVertex() noexcept = default;
    MuoniumSimVertex& operator=(const MuoniumSimVertex&) noexcept = default;
    MuoniumSimVertex& operator=(MuoniumSimVertex&&) noexcept = default;

    [[nodiscard]] const auto& GetTrueVertexTime() const { return fTrueVertexTime; }
    [[nodiscard]] const auto& GetTrueVertexPosition() const { return fTrueVertexPosition; }
    [[nodiscard]] const auto& GetTrueVertexEnergy() const { return fTrueVertexEnergy; }
    [[nodiscard]] const auto& GetTrueVertexMomentum() const { return fTrueVertexMomentum; }
    [[nodiscard]] const auto& GetTrueParticles() const { return fTrueParticles; }

    void SetTrueVertexTime(Double_t val) { fTrueVertexTime = val; }
    template<typename Vector3_t>
    void SetTrueVertexPosition(Vector3_t&& pos) { fTrueVertexPosition = std::forward<Vector3_t>(pos); }
    void SetTrueVertexPosition(Double_t x, Double_t y, Double_t z) { fTrueVertexPosition = {x, y, z}; }
    void SetTrueVertexEnergy(Double_t val) { fTrueVertexEnergy = val; }
    template<typename Vector3_t>
    void SetTrueVertexMomentum(Vector3_t&& pos) { fTrueVertexMomentum = std::forward<Vector3_t>(pos); }
    void SetTrueVertexMomentum(Double_t x, Double_t y, Double_t z) { fTrueVertexMomentum = {x, y, z}; }
    template<typename String_t>
    void SetTrueParticles(String_t&& particleNames) { fTrueParticles = std::forward<String_t>(particleNames); }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "MVtx"; }

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

} // namespace MACE::Core::DataModel::SimVertex
