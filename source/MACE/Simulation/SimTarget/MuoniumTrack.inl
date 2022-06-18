namespace MACE::Simulation::SimTarget {

inline void* MuoniumTrack::operator new(size_t) {
    if (fgMuoniumTrackAllocator == nullptr) {
        fgMuoniumTrackAllocator = new G4Allocator<MuoniumTrack>();
    }
    return static_cast<void*>(fgMuoniumTrackAllocator->MallocSingle());
}

inline void MuoniumTrack::operator delete(void* hit) {
    fgMuoniumTrackAllocator->FreeSingle(static_cast<MuoniumTrack*>(hit));
}

} // namespace MACE::Simulation::SimTarget
