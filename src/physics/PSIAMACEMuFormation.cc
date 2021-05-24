// PSIMACEMuFormation
//
// Author:	Yuzhe Mao
//
// Review and update: Shihan Zhao 05.2021
// 

#include "physics/PSIMACEMuFormation.hh"

#include "physics/PSIMACEMuoniumPlus.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "userAction/PSIMACEDetectorConstruction.hh"

using namespace CLHEP;

PSIMACEMuFormation::PSIMACEMuFormation(const G4String& name, G4ProcessType aType) :
    G4VDiscreteProcess(name, aType),
    fParticleChange(new G4ParticleChange()),
    fPhysicalSiO2Target(static_cast<const PSIMACEDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetPhysicalSiO2Target()) {}

PSIMACEMuFormation::~PSIMACEMuFormation() {
    delete fParticleChange;
}

G4VParticleChange* PSIMACEMuFormation::PostStepDoIt(const G4Track& track, const G4Step& step) {
    // Initialize ParticleChange  (by setting all its members equal to
    //                             the corresponding members in G4Track)
    fParticleChange->Initialize(track);

    if (!step.IsLastStepInVolume() &&
        step.GetTrack()->GetDynamicParticle()->GetKineticEnergy() > 0.5 * keV &&
        step.GetTrack()->GetVolume() == fPhysicalSiO2Target) {
        G4ThreadLocal static Yields Gonin;
        G4ThreadLocal static double yvector[3];
        Gonin.GetYields(
            step.GetTrack()->GetDynamicParticle()->GetKineticEnergy() / keV,
            105.658369 * 1000, yvector); // Energy [keV], muon mass [keV/c2], yield table

        if (G4UniformRand() > yvector[0]) {
            // mu+ convert to muonium.
            auto muonium = new G4DynamicParticle(*step.GetTrack()->GetDynamicParticle());
            muonium->SetDefinition(PSIMACEMuoniumPlus::Definition());

            auto muoniumTrack = new G4Track(muonium, track.GetGlobalTime(), track.GetPosition());
            auto r1 = G4UniformRand();
            auto a = 2. * sqrt(r1 * (1. - r1));
            auto r2 = 2. * M_PI * G4UniformRand();
            muoniumTrack->SetMomentumDirection(G4ThreeVector(a * cos(r2), a * sin(r2), 1. - 2. * r1));
            muoniumTrack->SetKineticEnergy(RandExponential::shoot(k_Boltzmann * 300. * kelvin));
            fParticleChange->AddSecondary(muoniumTrack);

            fParticleChange->ProposeTrackStatus(fStopAndKill);
        } // else mu+ stays unchanged.
    }

    return fParticleChange;
}

G4double PSIMACEMuFormation::GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition) {
    *condition = Forced;
    return std::numeric_limits<G4double>::max();
}
