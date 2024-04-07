#pragma once

#include "MACE/Extension/Geant4X/WrapAsMuoniumDecayChannel.h++"

#include "G4MuonRadiativeDecayChannelWithSpin.hh"

namespace MACE::inline Extension::Geant4X {

using MuoniumRadiativeDecayChannelWithSpin = WrapAsMuoniumDecayChannel<G4MuonRadiativeDecayChannelWithSpin,
                                                                       "MuoniumRadiativeDecayChannelWithSpin">;

} // namespace MACE::inline Extension::Geant4X
