#pragma once

#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimEMC::inline Hit {

class PMTHit final : public Geant4X::UseG4Allocator<PMTHit>,
                     public G4VHit {
public:
    auto Time() -> const auto& { return fTime; }
    auto CellID() -> const auto& { return fCellID; }

    auto Time(double v) -> void { fTime = v; }
    auto CellID(int v) -> void { fCellID = v; }

private:
    double fTime;
    int fCellID;
};

using PMTHitCollection = G4THitsCollection<PMTHit>;

} // namespace MACE::SimEMC::inline Hit
