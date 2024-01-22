#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Simulation/Generator/SurfaceMuon.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimMACE::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto TimeRMS(G4double val) -> void { fTimeWidthRMS = val; }
    auto MuonsForEachG4Event(G4int n) -> void { fMuonsForEachG4Event = n; }

    auto GetTimeWidthRMS() const -> auto { return fTimeWidthRMS; }
    auto MuonsForEachG4Event() const -> auto { return fMuonsForEachG4Event; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4double fTimeWidthRMS;
    G4int fMuonsForEachG4Event;
};

} // namespace MACE::SimMACE::inline Action
