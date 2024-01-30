#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace MACE::SimMACE {

inline namespace Action {
class PrimaryGeneratorAction;
} // namespace Action

inline namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Geant4X::SingletonMessenger<PrimaryGeneratorActionMessenger,
                                                                                 PrimaryGeneratorAction> {
    friend Env::Memory::SingletonInstantiator;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTimeRMS;
    std::unique_ptr<G4UIcmdWithAnInteger> fMuonsForEachG4Event;
};

} // namespace Messenger

} // namespace MACE::SimMACE
