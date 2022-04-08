#pragma once

#include "Core/DataModel/SimHit/MCPSimHit.hxx"
#include "Utility/ObserverPtr.hxx"

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::Simulation::SimMACE::Hit {

using Utility::ObserverPtr;

class MCPHit final : public G4VHit,
                     public Core::DataModel::SimHit::MCPSimHit {
    using Base = MCPSimHit;

public:
    MCPHit() noexcept = default;
    MCPHit(const MCPHit& hit) noexcept = default;
    MCPHit(MCPHit&& hit) noexcept = default;
    ~MCPHit() noexcept = default;
    MCPHit& operator=(const MCPHit& hit) noexcept = default;
    MCPHit& operator=(MCPHit&& hit) noexcept = default;

    void SetHitPosition(const G4TwoVector& pos) { Base::SetHitPosition(pos.x(), pos.y()); }
    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

    inline void* operator new(size_t);
    inline void operator delete(void*);

private:
    static ObserverPtr<G4Allocator<MCPHit>> fgMCPAllocator;
};

using MCPHitCollection = G4THitsCollection<MCPHit>;

inline void* MCPHit::operator new(size_t) {
    if (fgMCPAllocator == nullptr) {
        fgMCPAllocator = new G4Allocator<MCPHit>();
    }
    return static_cast<void*>(fgMCPAllocator->MallocSingle());
}

inline void MCPHit::operator delete(void* hit) {
    fgMCPAllocator->FreeSingle(static_cast<MCPHit*>(hit));
}

} // namespace MACE::Simulation::SimMACE::Hit
