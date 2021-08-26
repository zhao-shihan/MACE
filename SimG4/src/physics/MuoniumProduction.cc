#include "physics/MuoniumProduction.hh"

#include "physics/Muonium.hh"
#include "G4MuonPlus.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"

using namespace MACE::SimG4::Physics;

MuoniumProduction::MuoniumProduction(const G4String& name, G4ProcessType aType) :
    G4VRestProcess(name, aType),
    fParticleChange(new G4ParticleChange()) {}

MuoniumProduction::~MuoniumProduction() {
    delete fParticleChange;
}

G4VParticleChange* MuoniumProduction::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange->Initialize(track);
    
    auto muonium = new G4DynamicParticle(*track.GetDynamicParticle());
    muonium->SetDefinition(Muonium::Definition());

    auto muoniumTrack = new G4Track(muonium, track.GetGlobalTime(), track.GetPosition());
    auto cosTheta = 1.0 - 2.0 * G4UniformRand();
    auto sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    auto phi = twopi * G4UniformRand();
    muoniumTrack->SetMomentumDirection(G4ThreeVector(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta));
    muoniumTrack->SetKineticEnergy(G4RandExponential::shoot(k_Boltzmann * 300. * kelvin));
    fParticleChange->AddSecondary(muoniumTrack);

    fParticleChange->ProposeTrackStatus(fStopAndKill);
    
    return fParticleChange;
}

/* G4VParticleChange* MuoniumProduction::PostStepDoIt(const G4Track& track, const G4Step& step) {
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
            muonium->SetDefinition(MACEMuoniumPlus::Definition());

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

G4double MuoniumProduction::GetMeanFreePath(const G4Track&, G4double, G4ForceCondition* condition) {
    *condition = Forced;
    return std::numeric_limits<G4double>::max();
} */
