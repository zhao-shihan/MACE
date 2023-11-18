#pragma once

#include "MACE/Data/TupleModel/SimRawHit/EMCSimRawHit.c++"
#include "MACE/Extension/Geant4X/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace MACE::SimMACE::inline Hit {

class EMCRawHit final : public Data::EMCSimRawHit::Entry,
                        public Geant4X::UseG4Allocator<EMCRawHit>,
                        public G4VHit {};

using EMCRawHitCollection = G4THitsCollection<EMCRawHit>;

} // namespace MACE::SimMACE::inline Hit
