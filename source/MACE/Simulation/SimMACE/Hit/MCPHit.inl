namespace MACE::Simulation::SimMACE::Hit {

inline void* MCPHit::operator new(size_t) {
    if (fgMCPHitAllocator == nullptr) {
        fgMCPHitAllocator = new G4Allocator<MCPHit>();
    }
    return static_cast<void*>(fgMCPHitAllocator->MallocSingle());
}

inline void MCPHit::operator delete(void* hit) {
    fgMCPHitAllocator->FreeSingle(static_cast<MCPHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
