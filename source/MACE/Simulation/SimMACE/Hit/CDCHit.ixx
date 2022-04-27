namespace MACE::Simulation::SimMACE::Hit {

inline void* CDCHit::operator new(size_t) {
    if (fgCDCHitAllocator == nullptr) {
        fgCDCHitAllocator = new G4Allocator<CDCHit>();
    }
    return static_cast<void*>(fgCDCHitAllocator->MallocSingle());
}

inline void CDCHit::operator delete(void* hit) {
    fgCDCHitAllocator->FreeSingle(static_cast<CDCHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
