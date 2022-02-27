#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::PrimaryGeneratorAction final :
    public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction(ObserverPtr<const EventAction> eventAction);
    ~PrimaryGeneratorAction() noexcept = default;
    void GeneratePrimaries(G4Event* event) override;

    void SetFlux(G4double val) { fFlux = val; }
    void SetRepetitionRate(G4double val) { fRepetitionRate = val; }
    void SetTimeWidthRMS(G4double val) { fTimeWidthRMS = val; }
    void SetEnergy(G4double val) { fEnergy = val; }
    void SetEnergySpreadRMS(G4double val) { fEnergySpreadRMS = val; }
    void SetBeamProfileRMS(G4double val) { fBeamProfileRMS = val; }

    void SetMuonsPerG4Event(G4int n) { fMuonsPerG4Event = n; }

    auto GetRepetitionID() const { return fRepetitionID; }

private:
    const ObserverPtr<const EventAction> fEventAction;

    G4ParticleGun fParticleGun;

    G4double fFlux = 5e5_s_1;
    G4double fRepetitionRate = 2.5_Hz;
    G4double fTimeWidthRMS = 10_ms;
    G4double fEnergy = 1.5_MeV;
    G4double fEnergySpreadRMS = 0.05 * fEnergy;
    G4double fBeamProfileRMS = 5_mm;

    G4int    fMuonsPerG4Event = 2000;
    G4int    fRepetitionID;
};
