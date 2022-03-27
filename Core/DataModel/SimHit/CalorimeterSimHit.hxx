#pragma once

#include "DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "DataModel/Hit/CalorimeterHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using Utility::ShortString;

class CalorimeterSimHit : public Hit::CalorimeterHit {
    friend DataHub;

public:
    CalorimeterSimHit() noexcept;
    CalorimeterSimHit(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit(CalorimeterSimHit&& hit) noexcept = default;
    virtual ~CalorimeterSimHit() noexcept = default;
    CalorimeterSimHit& operator=(const CalorimeterSimHit& hit) noexcept = default;
    CalorimeterSimHit& operator=(CalorimeterSimHit&& hit) noexcept = default;

    [[nodiscard]] const auto& GetParticle() const { return fParticle; }
    [[nodiscard]] const auto& GetEventID() const { return fEventID; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    template<typename String_t>
    void SetParticle(String_t&& particleName) { fParticle = std::forward<String_t>(particleName); }
    void SetEventID(Int_t val) { fEventID = val; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    static consteval const char* BasicTreeName() noexcept { return "CalSimHit"; }

private:
    ShortString fParticle;
    Int_t fEventID;
    Int_t fTrackID;

    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgEventID;
    static IntBranchSocket fgTrackID;
};

} // namespace MACE::Core::DataModel::SimHit
