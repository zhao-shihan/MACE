#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

namespace MACE::SimMACE {

inline namespace Action {

class PrimaryGeneratorAction;

} // namespace Action

inline namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Env::Memory::Singleton<PrimaryGeneratorActionMessenger>,
                                              public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger();

public:
    auto Register(gsl::not_null<PrimaryGeneratorAction*> pga) -> void { fPrimaryGeneratorAction = pga; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    PrimaryGeneratorAction* fPrimaryGeneratorAction;

    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fTimeRMS;
    std::unique_ptr<G4UIcmdWithAnInteger> fMuonsForEachG4Event;
};

} // namespace Messenger

} // namespace MACE::SimMACE
