#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Simulation/Generator/SurfaceMuon.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimMACE::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    void TimeRMS(G4double val) { fTimeWidthRMS = val; }
    void MuonsForEachG4Event(G4int n) { fMuonsForEachG4Event = n; }

    const auto& GetTimeWidthRMS() const { return fTimeWidthRMS; }
    const auto& MuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    void GeneratePrimaries(G4Event* event) override;

private:
    Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4double fTimeWidthRMS;
    G4int fMuonsForEachG4Event;
};

} // namespace MACE::SimMACE::inline Action
