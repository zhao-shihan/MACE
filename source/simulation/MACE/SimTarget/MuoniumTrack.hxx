#pragma once

#include "MACE/DataModel/SimTrack/MuoniumSimTrack.hxx"
#include "MACE/Extension/Geant4X/UseG4Allocator.hxx"

#include "G4ThreeVector.hh"

namespace MACE::SimTarget {

class MuoniumTrack final : public DataModel::SimTrack::MuoniumSimTrack,
                           public Geant4X::UseG4Allocator<MuoniumTrack> {
public:
    MuoniumTrack() noexcept = default;
    ~MuoniumTrack() = default;

    MuoniumTrack(const MuoniumTrack&) noexcept = default;
    MuoniumTrack(MuoniumTrack&&) noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack&) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&&) noexcept = default;
};
static_assert(DataModel::TransientData<MuoniumTrack>);

} // namespace MACE::SimTarget
