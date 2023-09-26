#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimEMC::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto GeneratePrimaries(G4Event* event) -> void override;
};

} // namespace MACE::SimEMC::inline Action
