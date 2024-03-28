#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithAnInteger;

namespace MACE::inline Simulation::Analysis {

class MMSTruthTracker;

class MMSTruthTrackerMessenger final : public Geant4X::SingletonMessenger<MMSTruthTrackerMessenger,
                                                                          MMSTruthTracker> {
    friend Env::Memory::SingletonInstantiator;

private:
    MMSTruthTrackerMessenger();
    ~MMSTruthTrackerMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcmdWithAnInteger> fMinNCDCHitForQualifiedTrack;
    std::unique_ptr<G4UIcmdWithAnInteger> fMinNTTCHitForQualifiedTrack;
};

} // namespace MACE::inline Simulation::Analysis
