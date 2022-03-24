#pragma once

#include "DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "DataModel/BranchSocket/Vector3BranchSocket.hxx"
#include "DataModel/Hit/VertexDetectorHit.hxx"

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
    [[nodiscard]] const auto& GetParticleName() const { return fParticleName; }
    [[nodiscard]] const auto& GetEventID() const { return fEventID; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    void SetVertexTime(Double_t val) { fVertexTime = val; }
    template<typename Vector3_t>
    void SetVertexPosition(Vector3_t&& pos) { fVertexPosition = std::forward<Vector3_t>(pos); }
    void SetVertexPosition(Double_t x, Double_t y, Double_t z) { fVertexPosition.Set(x, y, z); }
    template<typename String_t>
    void SetParticleName(String_t&& particleName) { fParticleName = std::forward<String_t>(particleName); }
    void SetEventID(Int_t val) { fEventID = val; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "MCPSimHit"; }

private:
    Double_t fVertexTime;
    TEveVectorD fVertexPosition;
    ShortString fParticleName;
    Int_t fEventID;
    Int_t fTrackID;

    static DoubleBranchSocket fgVertexTime;
    static Vector3FBranchSocket fgVertexPosition;
    static ShortStringBranchSocket fgParticleName;
    static IntBranchSocket fgEventID;
    static IntBranchSocket fgTrackID;
};

inline void VertexDetectorSimHit::FillBranchSockets() const noexcept {
    VertexDetectorHit::FillBranchSockets();
    fgVertexTime.SetValue(fVertexTime);
    fgVertexPosition.SetValue(fVertexPosition);
    fgParticleName.SetValue(fParticleName);
    fgEventID.SetValue(fEventID);
    fgTrackID.SetValue(fTrackID);
}

} // namespace MACE::Core::DataModel::SimHit
