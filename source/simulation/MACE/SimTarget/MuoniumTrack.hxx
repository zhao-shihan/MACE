#pragma once

#include "MACE/Core/DataModel/SimTrack/MuoniumSimTrack.hxx"
#include "MACE/Geant4X/UseG4Allocator.hxx"

#include "G4ThreeVector.hh"

namespace MACE::SimTarget {

class MuoniumTrack final : public Geant4X::UseG4Allocator<MuoniumTrack>,
                           public Core::DataModel::SimTrack::MuoniumTrack {
    using Base = Core::DataModel::SimTrack::MuoniumTrack;

public:
    MuoniumTrack() noexcept = default;
    MuoniumTrack(const MuoniumTrack&) noexcept = default;
    MuoniumTrack(MuoniumTrack&&) noexcept = default;
    ~MuoniumTrack() noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack&) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&&) noexcept = default;

    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(const G4ThreeVector& mom) { Base::SetVertexMomentum(mom.x(), mom.y(), mom.z()); }
    void SetDecayPosition(const G4ThreeVector& pos) { Base::SetDecayPosition(pos.x(), pos.y(), pos.z()); }
    void SetDecayMomentum(const G4ThreeVector& mom) { Base::SetDecayMomentum(mom.x(), mom.y(), mom.z()); }
};

} // namespace MACE::SimTarget
