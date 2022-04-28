namespace MACE::Simulation::SimMACE::Hit {

inline void* EMCalHit::operator new(size_t) {
    if (fgEMCalHitAllocator == nullptr) {
        fgEMCalHitAllocator = new G4Allocator<EMCalHit>();
    }
    return static_cast<void*>(fgEMCalHitAllocator->MallocSingle());
}

inline void EMCalHit::operator delete(void* hit) {
    fgEMCalHitAllocator->FreeSingle(static_cast<EMCalHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
