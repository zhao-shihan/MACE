#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/BranchSocket/VectorBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/MCPHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class MCPSimHit : public Hit::MCPHit {
public:
    MCPSimHit() noexcept;
    MCPSimHit(const MCPSimHit& hit) noexcept = default;
    MCPSimHit(MCPSimHit&& hit) noexcept = default;
    virtual ~MCPSimHit() noexcept = default;
    MCPSimHit& operator=(const MCPSimHit& hit) noexcept = default;
    MCPSimHit& operator=(MCPSimHit&& hit) noexcept = default;

    const auto& GetVertexTime() const { return fVertexTime; }
    const auto& GetVertexPosition() const { return fVertexPosition; }
    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3T>
    void SetVertexPosition(Vector3T&& pos) { fVertexPosition = std::forward<Vector3T>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition = {x, y, z}; }
    template<typename StringT>
    void SetParticle(StringT&& particleName) { fParticle = std::forward<StringT>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

    static consteval const char* BasicTreeName() noexcept { return "MCPSimHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    Double_t fVertexTime;
    Eigen::Vector3d fVertexPosition;
    ShortString fParticle;
    Int_t fG4EventID;
    Int_t fG4TrackID;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
};

} // namespace MACE::Core::DataModel::SimHit
