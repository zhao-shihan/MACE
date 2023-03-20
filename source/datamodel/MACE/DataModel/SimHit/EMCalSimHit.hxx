#pragma once

#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/Hit/EMCalHit.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel::inline SimHit {

class EMCalSimHit : public EMCalHit {
public:
    inline EMCalSimHit() noexcept;
    virtual ~EMCalSimHit() = default;

    EMCalSimHit(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit(EMCalSimHit&& hit) noexcept = default;
    EMCalSimHit& operator=(const EMCalSimHit& hit) noexcept = default;
    EMCalSimHit& operator=(EMCalSimHit&& hit) noexcept = default;

    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }
    const auto& Particle() const { return fParticle; }

    void G4EventID(int val) { fG4EventID = val; }
    void G4TrackID(int val) { fG4TrackID = val; }
    void Particle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }

    inline void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return std::string_view("EMCalSimHit"); }

private:
    int fG4EventID;
    int fG4TrackID;
    ShortString fParticle;

    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
    static ShortStringBranchSocket fgParticle;
};
static_assert(TransientData<EMCalSimHit>);

} // namespace MACE::DataModel::inline SimHit

#include "MACE/DataModel/SimHit/EMCalSimHit.inl"
