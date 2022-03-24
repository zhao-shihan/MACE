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

    [[nodiscard]] const auto& GetParticleName() const { return fParticleName; }
    [[nodiscard]] const auto& GetEventID() const { return fEventID; }
    [[nodiscard]] const auto& GetTrackID() const { return fTrackID; }

    template<typename String_t>
    void SetParticleName(String_t&& particleName) { fParticleName = std::forward<String_t>(particleName); }
    void SetEventID(Int_t val) { fEventID = val; }
    void SetTrackID(Int_t val) { fTrackID = val; }

protected:
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    inline void FillBranchSockets() const noexcept;

private:
    static constexpr const char* BasicName() { return "CalSimHit"; }

private:
    ShortString fParticleName;
    Int_t fEventID;
    Int_t fTrackID;

    static ShortStringBranchSocket fgParticleName;
    static IntBranchSocket fgEventID;
    static IntBranchSocket fgTrackID;
};

inline void CalorimeterSimHit::FillBranchSockets() const noexcept {
    CalorimeterHit::FillBranchSockets();
    fgParticleName.SetValue(fParticleName);
    fgEventID.SetValue(fEventID);
    fgTrackID.SetValue(fTrackID);
}

} // namespace MACE::Core::DataModel::SimHit
