#pragma once

#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class SiPMHit final : public Geant4X::UseG4Allocator<SiPMHit>,
                      public G4VHit {
public:
    auto Time() -> const auto& { return fTime; }
    auto Energy() -> const auto& { return fEnergy; }

    auto Time(G4double v) -> void { fTime = v; }
    auto Energy(G4double v) -> void { fEnergy = v; }

private:
    G4double fTime;
    G4double fEnergy;
};

using SiPMHitCollection = G4THitsCollection<SiPMHit>;

} // namespace MACE::SimMACE::inline Hit
