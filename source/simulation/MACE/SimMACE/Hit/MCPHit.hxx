#pragma once

#include "MACE/Core/DataModel/SimHit/MCPSimHit.hxx"
#include "MACE/SimulationG4/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

class MCPHit final : public SimulationG4::UseG4Allocator<MCPHit>,
                     public G4VHit,
                     public Core::DataModel::SimHit::MCPSimHit {
public:
    MCPHit() noexcept = default;
    MCPHit(const MCPHit& hit) noexcept = default;
    MCPHit(MCPHit&& hit) noexcept = default;
    ~MCPHit() noexcept = default;
    MCPHit& operator=(const MCPHit& hit) noexcept = default;
    MCPHit& operator=(MCPHit&& hit) noexcept = default;

    void SetHitPosition(const G4TwoVector& pos) { MCPSimHit::SetHitPosition(pos.x(), pos.y()); }
    void SetVertexPosition(const G4ThreeVector& pos) { MCPSimHit::SetVertexPosition(pos.x(), pos.y(), pos.z()); }
};

using MCPHitCollection = G4THitsCollection<MCPHit>;

} // namespace MACE::SimMACE::Hit
