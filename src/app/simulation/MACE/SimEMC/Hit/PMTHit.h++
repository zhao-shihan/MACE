#pragma once

#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimEMC::inline Hit {

class PMTHit final : public Geant4X::UseG4Allocator<PMTHit>,
                     public G4VHit {
public:
    auto Time() -> const auto& { return fTime; }
    auto CopyNo() -> const auto& { return fCopyNo; }

    auto Time(double v) -> void { fTime = v; }
    auto CopyNo(int v) -> void { fCopyNo = v; }

private:
    double fTime;
    int fCopyNo;
};

using PMTHitCollection = G4THitsCollection<PMTHit>;

} // namespace MACE::SimEMC::inline Hit
