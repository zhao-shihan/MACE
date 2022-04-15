#include "MACE/Simulation/Physics/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Muonium.hxx"
#include "MACE/Simulation/Physics/MuoniumProduction.hxx"
#include "MACE/Simulation/SimMACE/Messenger/PhysicsMessenger.hxx"

#include "G4MuonPlus.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"

namespace MACE::Simulation::Physics {

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

} // namespace MACE::Simulation::Physics
