#pragma once

#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannel.h++"
#include "MACE/Simulation/Physics/DecayChannel/MuonInternalPairProductionDecayChannelMessenger.h++"
#include "MACE/Simulation/Physics/DecayChannel/WrapAsMuoniumDecayChannel.h++"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuoniumInternalPairProductionDecayChannel : public WrapAsMuoniumDecayChannel<MuonInternalPairProductionDecayChannel, "MuoniumIPPDecay"> {
public:
    MuoniumInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose = 1);

private:
    MuonInternalPairProductionDecayChannelMessenger::Register<MuonInternalPairProductionDecayChannel> fMessengerRegister;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
