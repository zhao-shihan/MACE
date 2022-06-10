#pragma once

#include "MACE/Core/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/Core/DataModel/Hit/EMCalHit.hxx"

namespace MACE::Core::DataModel::SimHit {

using BranchSocket::IntBranchSocket;
using BranchSocket::ShortStringBranchSocket;
using Utility::ShortString;

class EMCalSimHit : public Hit::EMCalHit {
public:
    EMCalSimHit() noexcept;
    EMCalSimHit(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit(EMCalSimHit&& hit) noexcept = default;
    virtual ~EMCalSimHit() noexcept = default;
    EMCalSimHit& operator=(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit& operator=(EMCalSimHit&& hit) noexcept = default;

    const auto& GetParticle() const { return fParticle; }
    const auto& GetG4EventID() const { return fG4EventID; }
    const auto& GetG4TrackID() const { return fG4TrackID; }

    template<typename StringT>
    void SetParticle(StringT&& particleName) { fParticle = std::forward<StringT>(particleName); }
    void SetG4EventID(Int_t val) { fG4EventID = val; }
    void SetG4TrackID(Int_t val) { fG4TrackID = val; }

    static consteval const char* BasicTreeName() noexcept { return "CalSimHit"; }
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    void FillBranchSockets() const noexcept;

private:
    ShortString fParticle;
    Int_t fG4EventID;
    Int_t fG4TrackID;

    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
};

} // namespace MACE::Core::DataModel::SimHit
