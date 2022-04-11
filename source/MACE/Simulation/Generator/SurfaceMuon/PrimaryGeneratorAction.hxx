/// A generator generates surface muon beam.

#pragma once

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::Simulation::Generator::SurfaceMuon {

class PrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() noexcept = default;
    PrimaryGeneratorAction(const PrimaryGeneratorAction&) = delete;
    PrimaryGeneratorAction& operator=(const PrimaryGeneratorAction&) = delete;

    void GeneratePrimaries(G4Event* event) override;

    void SetFlux(G4double val) { fFlux = val; }
    void SetRepetitionRate(G4double val) { fRepetitionRate = val; }
    void SetTimeWidthRMS(G4double val) { fTimeWidthRMS = val; }
    void SetEnergy(G4double val) { fEnergy = val; }
    void SetEnergySpreadRMS(G4double val) { fEnergySpreadRMS = val; }
    void SetBeamProfileRMS(G4double val) { fBeamProfileRMS = val; }
    void SetVertexZ(G4double val) { fVertexZ = val; }

    void SetMuonsForEachG4Event(size_t n) { fSurfaceMuonsOfThisG4Event.resize(n); }

    auto GetRepetitionID() const { return fRepetitionID; }

private:
    G4ParticleGun fSurfaceMuonBeam;

    G4double fFlux;
    G4double fRepetitionRate;
    G4double fTimeWidthRMS;
    G4double fEnergy;
    G4double fEnergySpreadRMS;
    G4double fBeamProfileRMS;
    G4double fVertexZ;

    std::vector<std::tuple<G4double, G4ThreeVector, G4double>> fSurfaceMuonsOfThisG4Event;

    G4int fRepetitionID;
};

} // namespace MACE::Simulation::Generator::SurfaceMuon
