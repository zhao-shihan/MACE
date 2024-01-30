#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UIcmdWithABool.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;

namespace MACE::SimEMC {

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
    auto AssignTo(gsl::not_null<PrimaryGeneratorAction*> pga) -> void { fPrimaryGeneratorAction = pga; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    PrimaryGeneratorAction* fPrimaryGeneratorAction;

    std::unique_ptr<G4UIcommand> fSwitchToGPS;
    std::unique_ptr<G4UIcommand> fSwitchToCosmicRayMuon;
};

} // namespace Messenger

} // namespace MACE::SimEMC
