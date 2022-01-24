#include "G4MuonPlus.hh"
#include "G4RunManager.hh"

#include "SimMACE/Physics/MuoniumProduction.hxx"
#include "SimMACE/Physics/AntiMuonium.hxx"
#include "SimMACE/Physics/Muonium.hxx"
#include "SimMACE/Messenger/PhysicsMessenger.hxx"

using namespace MACE::SimMACE::Physics;

MuoniumProduction::MuoniumProduction(const G4String& name, G4ProcessType aType) :
    G4VRestProcess(name, aType),
    fParticleChange(new G4ParticleChange()) {
    Messenger::PhysicsMessenger::Instance()->Set(this);
}

MuoniumProduction::~MuoniumProduction() {
    delete fParticleChange;
}

G4VParticleChange* MuoniumProduction::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange->Initialize(track);

    G4ParticleDefinition* muonium;
    if (G4UniformRand() < fConversionProbability) {
        muonium = AntiMuonium::Definition();
    } else {
        muonium = Muonium::Definition();
    }
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    muoniumDynamicParticle->SetDefinition(muonium);
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(muonium->GetPDGLifeTime()));
    muoniumDynamicParticle->SetKineticEnergy(k_Boltzmann * 300 * kelvin);

    fParticleChange->AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));

    fParticleChange->ProposeTrackStatus(fStopAndKill);

    return fParticleChange;
}
