#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4UserRunAction.hh"

namespace MACE::SimMACE::inline Action {

class RunAction final : public Env::Memory::PassiveSingleton<RunAction>,
                        public G4UserRunAction {
public:
    auto BeginOfRunAction(const G4Run*) -> void override;
    auto EndOfRunAction(const G4Run* run) -> void override;
};

} // namespace MACE::SimMACE::inline Action
