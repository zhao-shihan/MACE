#include "MACE/Simulation/Physics/DecayChannel/MuoniumInternalPairProductionDecayChannel.h++"

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

MuoniumInternalPairProductionDecayChannel::MuoniumInternalPairProductionDecayChannel(const G4String& parentName, G4double br, G4int verbose) :
    WrapAsMuoniumDecayChannel{parentName, br, verbose},
    fMessengerRegister{this} {}

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
