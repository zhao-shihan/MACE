#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcommand;

namespace MACE::SimEMC {

class PhysicsList;

inline namespace Messenger {

class PhysicsListMessenger final : public Env::Memory::Singleton<PhysicsListMessenger>,
                                   public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    PhysicsListMessenger();
    ~PhysicsListMessenger();

public:
    auto AssignTo(gsl::not_null<PhysicsList*> pl) -> void { fPhysicsList = pl; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    PhysicsList* fPhysicsList;

    std::unique_ptr<G4UIcommand> fUseOpticalPhysics;
};

} // namespace Messenger

} // namespace MACE::SimEMC
