#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Extension/Geant4X/Generator/SurfaceMuon.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::inline Simulation::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    void MuonsForEachG4Event(G4int n) { fMuonsForEachG4Event = n; }
    const auto& MuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    void GeneratePrimaries(G4Event* event) override;

private:
    Geant4X::Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4int fMuonsForEachG4Event;
};

} // namespace MACE::inline Simulation::SimTarget::inline Action
