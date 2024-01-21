#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;

namespace MACE::inline Simulation::inline Physics::inline DecayChannel {

class MuonInternalPairProductionDecayChannel;

class MuonInternalPairProductionDecayChannelMessenger final : public Env::Memory::Singleton<MuonInternalPairProductionDecayChannelMessenger>,
                                                              public G4UImessenger {
    friend class Env::Memory::SingletonInstantiator;

private:
    MuonInternalPairProductionDecayChannelMessenger();
    ~MuonInternalPairProductionDecayChannelMessenger();

public:
    auto Register(gsl::not_null<MuonInternalPairProductionDecayChannel*> dc) -> void { fMuonInternalPairProductionDecayChannel = dc; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    MuonInternalPairProductionDecayChannel* fMuonInternalPairProductionDecayChannel;

    std::unique_ptr<G4UIdirectory> fMuonIPPDecayDirectory;

    std::unique_ptr<G4UIcmdWithADouble> fMetropolisDelta;
    std::unique_ptr<G4UIcmdWithAnInteger> fMetropolisDiscard;
    std::unique_ptr<G4UIcmdWithAnInteger> fMetropolisWarmupCycle;
    std::unique_ptr<G4UIcmdWithADouble> fSameChargedFinalStateEnergyCut;
};

} // namespace MACE::inline Simulation::inline Physics::inline DecayChannel
