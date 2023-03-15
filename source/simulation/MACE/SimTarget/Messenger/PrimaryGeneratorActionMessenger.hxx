#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithAnInteger;

namespace MACE::SimTarget {

namespace Action {

class PrimaryGeneratorAction;

} // namespace Action

namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Env::Memory::Singleton<PrimaryGeneratorActionMessenger>,
                                              public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger();

public:
    void AssignTo(gsl::not_null<Action::PrimaryGeneratorAction*> pga) { fPrimaryGeneratorAction = pga; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::PrimaryGeneratorAction* fPrimaryGeneratorAction;

    std::unique_ptr<G4UIcmdWithAnInteger> fMuonsForEachG4Event;
};

} // namespace Messenger

} // namespace MACE::SimTarget
