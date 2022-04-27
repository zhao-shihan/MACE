#pragma once

#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

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

    inline void* operator new(size_t);
    inline void operator delete(void*);

    void SetHitPosition(const G4TwoVector& pos) { Base::SetHitPosition(pos.x(), pos.y()); }
    void SetVertexPosition(const G4ThreeVector& pos) { Base::SetVertexPosition(pos.x(), pos.y(), pos.z()); }

private:
    static ObserverPtr<G4Allocator<MCPHit>> fgMCPHitAllocator;
};

using MCPHitCollection = G4THitsCollection<MCPHit>;

} // namespace MACE::Simulation::SimMACE::Hit

#include "MACE/Simulation/SimMACE/Hit/MCPHit.ixx"
