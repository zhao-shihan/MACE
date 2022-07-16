#pragma once

#include "MACE/Core/DataModel/SimTrack/MuoniumSimTrack.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

namespace MACE::Simulation::SimTarget {

using Utility::ObserverPtr;

class MuoniumTrack : public Core::DataModel::SimTrack::MuoniumTrack {
    using Base = Core::DataModel::SimTrack::MuoniumTrack;

public:
    MuoniumTrack() noexcept = default;
    MuoniumTrack(const MuoniumTrack&) noexcept = default;
    MuoniumTrack(MuoniumTrack&&) noexcept = default;
    virtual ~MuoniumTrack() noexcept = default;
    MuoniumTrack& operator=(const MuoniumTrack&) noexcept = default;
    MuoniumTrack& operator=(MuoniumTrack&&) noexcept = default;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
    void SetVertexMomentum(const G4ThreeVector& mom) { Base::SetVertexMomentum(mom.x(), mom.y(), mom.z()); }
    void SetDecayPosition(const G4ThreeVector& pos) { Base::SetDecayPosition(pos.x(), pos.y(), pos.z()); }
    void SetDecayMomentum(const G4ThreeVector& mom) { Base::SetDecayMomentum(mom.x(), mom.y(), mom.z()); }

private:
    static ObserverPtr<G4Allocator<MuoniumTrack>> fgMuoniumTrackAllocator;
};

} // namespace MACE::Simulation::SimTarget

#include "MACE/Simulation/SimTarget/MuoniumTrack.inl"
