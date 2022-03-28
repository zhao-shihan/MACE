#pragma once

#include "Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "Core/DataModel/BranchSocket/Vector3BranchSocket.hxx"
#include "Core/DataModel/Hit/VertexDetectorHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::DoubleBranchSocket;
using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using BranchSocket::Vector3FBranchSocket;
using Utility::ShortString;

class VertexDetectorSimHit : public Hit::VertexDetectorHit {
    friend DataHub;

public:
    VertexDetectorSimHit() noexcept;
    VertexDetectorSimHit(const VertexDetectorSimHit& hit) noexcept = default;
    VertexDetectorSimHit(VertexDetectorSimHit&& hit) noexcept = default;
    virtual ~VertexDetectorSimHit() noexcept = default;
    VertexDetectorSimHit& operator=(const VertexDetectorSimHit& hit) noexcept = default;
    VertexDetectorSimHit& operator=(VertexDetectorSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetVertexTime() const { return fVertexTime; }
    [[nodiscard]] const auto& GetVertexPosition() const { return fVertexPosition; }
    [[nodiscard]] const auto& GetParticle() const { return fParticle; }
    [[nodiscard]] const auto& GetG4EventID() const { return fG4EventID; }
    [[nodiscard]] const auto& GetG4TrackID() const { return fG4TrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "MCPSimHit"; }

private:
    Double_t fVertexTime;
    TEveVectorD fVertexPosition;
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
