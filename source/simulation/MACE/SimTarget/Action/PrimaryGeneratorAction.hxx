#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"
#include "MACE/Geant4X/Generator/SurfaceMuon.hxx"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::Action {

class PrimaryGeneratorAction final : public Env::Memory::FreeSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    void SetMuonsForEachG4Event(G4int n) { fMuonsForEachG4Event = n; }
    const auto& GetMuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    void GeneratePrimaries(G4Event* event) override;

private:
    Geant4X::Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4int fMuonsForEachG4Event;
};

} // namespace MACE::SimTarget::Action
