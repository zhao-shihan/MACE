#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIdirectory;

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuonInternalPairProductionDecayChannel;

class MuonInternalPairProductionDecayChannelMessenger final : public Geant4X::SingletonMessenger<MuonInternalPairProductionDecayChannelMessenger,
                                                                                                 MuonInternalPairProductionDecayChannel> {
    friend class Env::Memory::SingletonInstantiator;

private:
    MuonInternalPairProductionDecayChannelMessenger();
    ~MuonInternalPairProductionDecayChannelMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithADouble> fMetropolisDelta;
    std::unique_ptr<G4UIcmdWithAnInteger> fMetropolisDiscard;
    std::unique_ptr<G4UIcmdWithABool> fApplyMACESpecificPxyCut;
    std::unique_ptr<G4UIcmdWithABool> fApplyMACESpecificPzCut;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
