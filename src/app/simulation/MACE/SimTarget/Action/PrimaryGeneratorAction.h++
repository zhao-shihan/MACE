#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Simulation/Generator/SurfaceMuon.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto MuonsForEachG4Event(G4int n) -> void { fMuonsForEachG4Event = n; }
    auto MuonsForEachG4Event() const -> const auto& { return fMuonsForEachG4Event; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4int fMuonsForEachG4Event;
};

} // namespace MACE::SimTarget::inline Action
