#pragma once

#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"
#include "MACE/SimulationG4/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

class EMCalHit final : public SimulationG4::UseG4Allocator<EMCalHit>,
                       public G4VHit,
                       public Core::DataModel::SimHit::EMCalSimHit {
public:
    EMCalHit() noexcept = default;
    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    ~EMCalHit() noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;
};

using EMCalHitCollection = G4THitsCollection<EMCalHit>;

} // namespace MACE::SimMACE::Hit
