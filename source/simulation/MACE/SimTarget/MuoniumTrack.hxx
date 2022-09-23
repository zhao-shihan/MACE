#pragma once

#include "MACE/Core/DataModel/SimTrack/MuoniumSimTrack.hxx"
#include "MACE/Geant4X/UseG4Allocator.hxx"

#include "G4ThreeVector.hh"

namespace MACE::SimTarget {

class MuoniumTrack final : public Core::DataModel::SimTrack::MuoniumSimTrack,
                           public Geant4X::UseG4Allocator<MuoniumTrack> {
public:
    MuoniumTrack() noexcept = default;
    ~MuoniumTrack() = default;

    MuoniumTrack(const MuoniumTrack&) noexcept = default;
    MuoniumTrack(MuoniumTrack&&) noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack&) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&&) noexcept = default;
};
static_assert(Core::DataModel::TransientData<MuoniumTrack>);

} // namespace MACE::SimTarget
