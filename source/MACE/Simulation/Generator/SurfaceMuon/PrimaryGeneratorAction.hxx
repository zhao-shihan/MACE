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
    void SetMuonsForEachG4Event(size_t n) { fMuonsForEachG4Event = n; }

    const auto& GetFlux() const { return fFlux; }
    const auto& GetRepetitionRate() const { return fRepetitionRate; }
    const auto& GetTimeWidthRMS() const { return fTimeWidthRMS; }
    const auto& GetEnergy() const { return fEnergy; }
    const auto& GetEnergySpreadRMS() const { return fEnergySpreadRMS; }
    const auto& GetBeamProfileRMS() const { return fBeamProfileRMS; }
    const auto& GetVertexZ() const { return fVertexZ; }
    const auto& GetMuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    const auto& GetRepetitionID() const { return fRepetitionID; }

private:
    G4ParticleGun fSurfaceMuonBeam;

    G4double fFlux;
    G4double fRepetitionRate;
    G4double fTimeWidthRMS;
    G4double fEnergy;
    G4double fEnergySpreadRMS;
    G4double fBeamProfileRMS;
    G4double fVertexZ;
    G4int fMuonsForEachG4Event;

    G4int fRepetitionID;
};

} // namespace MACE::Simulation::Generator::SurfaceMuon
