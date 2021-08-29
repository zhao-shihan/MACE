#include "G4MuonPlus.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"

#include "physics/MuoniumProduction.hh"
#include "physics/Muonium.hh"

using namespace MACE::SimG4::Physics;

MuoniumProduction::MuoniumProduction(const G4String& name, G4ProcessType aType) :
    G4VRestProcess(name, aType),
    fParticleChange(new G4ParticleChange()) {}

MuoniumProduction::~MuoniumProduction() {
    delete fParticleChange;
}

G4VParticleChange* MuoniumProduction::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange->Initialize(track);

    auto muonium = Muonium::Definition();
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    muoniumDynamicParticle->SetDefinition(muonium);
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(muonium->GetPDGLifeTime()));
    muoniumDynamicParticle->SetKineticEnergy(k_Boltzmann * 300 * kelvin);

    auto muoniumTrack = new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition());
    fParticleChange->AddSecondary(muoniumTrack);

    fParticleChange->ProposeTrackStatus(fStopAndKill);

    return fParticleChange;
}
