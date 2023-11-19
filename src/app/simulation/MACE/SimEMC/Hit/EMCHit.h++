#pragma once

#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimEMC::inline Hit {

class EMCHit final : public Geant4X::UseG4Allocator<EMCHit>,
                     public G4VHit {
public:
    auto Energy() -> const auto& { return fEdep; }
    auto Energy(double v) -> void { fEdep += v; }

private:
    double fEdep = 0.;
};

using EMCHitCollection = G4THitsCollection<EMCHit>;

} // namespace MACE::SimEMC::inline Hit
