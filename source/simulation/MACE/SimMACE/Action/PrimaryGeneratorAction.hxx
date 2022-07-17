#pragma once

#include "MACE/Simulation/Generator/SurfaceMuon.hxx"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimMACE::Action {

class PrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() noexcept = default;
    PrimaryGeneratorAction(const PrimaryGeneratorAction&) = delete;
    PrimaryGeneratorAction& operator=(const PrimaryGeneratorAction&) = delete;

    void SetFlux(G4double val) { fFlux = val; }
    void SetRepetitionRate(G4double val) { fRepetitionRate = val; }
    void SetTimeWidthRMS(G4double val) { fTimeWidthRMS = val; }
    void SetMuonsForEachG4Event(G4int n) { fMuonsForEachG4Event = n; }

    const auto& GetFlux() const { return fFlux; }
    const auto& GetRepetitionRate() const { return fRepetitionRate; }
    const auto& GetTimeWidthRMS() const { return fTimeWidthRMS; }
    const auto& GetMuonsForEachG4Event() const { return fMuonsForEachG4Event; }

    void GeneratePrimaries(G4Event* event) override;

    const auto& GetRepetitionID() const { return fRepetitionID; }

private:
    Simulation::Generator::SurfaceMuon fSurfaceMuonGenerator;

    G4double fFlux;
    G4double fRepetitionRate;
    G4double fTimeWidthRMS;
    G4int fMuonsForEachG4Event;

    G4int fRepetitionID;
};

} // namespace MACE::SimMACE::Action
