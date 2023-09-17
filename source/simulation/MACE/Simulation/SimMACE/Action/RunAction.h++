#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserRunAction.hh"

namespace MACE::inline Simulation::SimMACE::inline Action {

class RunAction final : public Env::Memory::PassiveSingleton<RunAction>,
                        public G4UserRunAction {
public:
    void BeginOfRunAction(const G4Run* run) override;
    void EndOfRunAction(const G4Run*) override;
};

} // namespace MACE::inline Simulation::SimMACE::inline Action
