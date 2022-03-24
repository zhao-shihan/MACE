#include "SimMACE/Messenger/PhysicsMessenger.hxx"
#include "SimMACE/Physics/AntiMuonium.hxx"
#include "SimMACE/Physics/Muonium.hxx"
#include "SimMACE/Physics/MuoniumProduction.hxx"

#include "G4MuonPlus.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"

using namespace MACE::Simulation::SimMACE::Physics;
using namespace MACE::Utility::LiteralUnit;
using MACE::Simulation::SimMACE::Messenger::PhysicsMessenger;

MuoniumProduction::MuoniumProduction() :
    G4VRestProcess("MuoniumProduction", fElectromagnetic),
    fParticleChange() {
    PhysicsMessenger::Instance().Set(this);
}

G4VParticleChange* MuoniumProduction::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);

    G4ParticleDefinition* muonium;
    if (G4UniformRand() < fConversionProbability) {
        muonium = AntiMuonium::Definition();
    } else {
        muonium = Muonium::Definition();
    }
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    muoniumDynamicParticle->SetDefinition(muonium);
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(G4Random::getTheEngine(), muonium->GetPDGLifeTime()));
    muoniumDynamicParticle->SetKineticEnergy(k_Boltzmann * 300_K);

    fParticleChange.AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));

    fParticleChange.ProposeTrackStatus(fStopAndKill);

    return std::addressof(fParticleChange);
}
