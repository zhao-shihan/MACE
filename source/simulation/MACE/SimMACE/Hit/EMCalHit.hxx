#pragma once

#include "MACE/Core/DataModel/SimHit/EMCalSimHit.hxx"
#include "MACE/Geant4X/UseG4Allocator.hxx"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::Hit {

class EMCalHit final : public Core::DataModel::SimHit::EMCalSimHit,
                       public Geant4X::UseG4Allocator<EMCalHit>,
                       public G4VHit {
public:
    EMCalHit() noexcept = default;
    ~EMCalHit() = default;

    EMCalHit(const EMCalHit& hit) noexcept = default;
    EMCalHit(EMCalHit&& hit) noexcept = default;
    EMCalHit& operator=(const EMCalHit& hit) noexcept = default;
    EMCalHit& operator=(EMCalHit&& hit) noexcept = default;
};
static_assert(Core::DataModel::TransientData<EMCalHit>);

using EMCalHitCollection = G4THitsCollection<EMCalHit>;

} // namespace MACE::SimMACE::Hit
