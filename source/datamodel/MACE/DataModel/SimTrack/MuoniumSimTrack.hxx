#pragma once

#include "MACE/DataModel/BranchSocket/ShortStringBranchSocket.hxx"
#include "MACE/DataModel/Track/MuoniumTrack.hxx"

#include <string_view>
#include <utility>

namespace MACE::DataModel::inline SimTrack {

using namespace std::string_view_literals;

class MuoniumSimTrack : public MuoniumTrack {
public:
    MuoniumSimTrack() noexcept;
    virtual ~MuoniumSimTrack() = default;

    MuoniumSimTrack(const MuoniumSimTrack& hit) noexcept = default;
    MuoniumSimTrack(MuoniumSimTrack&& hit) noexcept = default;
    MuoniumSimTrack& operator=(const MuoniumSimTrack& hit) noexcept = default;
    MuoniumSimTrack& operator=(MuoniumSimTrack&& hit) noexcept = default;

    const auto& Particle() const { return fParticle; }
    const auto& G4EventID() const { return fG4EventID; }
    const auto& G4TrackID() const { return fG4TrackID; }

    void Particle(auto&& p) { fParticle = std::forward<decltype(p)>(p); }
    void G4EventID(int val) { fG4EventID = val; }
    void G4TrackID(int val) { fG4TrackID = val; }

    void FillBranchSockets() const noexcept;
    static void CreateBranches(TTree& tree);
    static void ConnectToBranches(TTree& tree);
    static constexpr auto BasicTreeName() noexcept { return "MSimTrk"sv; }

private:
    ShortString fParticle;
    int fG4EventID;
    int fG4TrackID;

    static ShortStringBranchSocket fgParticle;
    static IntBranchSocket fgG4EventID;
    static IntBranchSocket fgG4TrackID;
};
static_assert(TransientData<MuoniumSimTrack>);

} // namespace MACE::DataModel::inline SimTrack
