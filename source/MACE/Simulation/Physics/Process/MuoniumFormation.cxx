// #include "MACE/Simulation/SimMACE/Messenger/PhysicsMessenger.hxx"
#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4MuonPlus.hh"
#include "G4RunManager.hh"

namespace MACE::Simulation::Physics::Process {

// using MACE::Simulation::SimMACE::Messenger::PhysicsMessenger;
using namespace Utility::LiteralUnit::Time;
using namespace Utility::PhysicalConstant;

MuoniumFormation::MuoniumFormation() :
    G4VRestProcess("MuoniumFormation", fElectromagnetic),
    fTarget(std::addressof(Target::Instance())),
    fParticleChange(),
    fMeanLifeTime(1.46467_us), // 60%
    fConversionProbability(8.3e-11) {
    // PhysicsMessenger::Instance().Set(this);
}

G4VParticleChange* MuoniumFormation::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    // The dynamic particle
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    // Determine whether the muonium is converted
    muoniumDynamicParticle->SetDefinition(
        (G4UniformRand() < fConversionProbability) ?
            static_cast<G4ParticleDefinition*>(Particle::AntiMuonium::Definition()) :
            static_cast<G4ParticleDefinition*>(Particle::Muonium::Definition()));
    // Sampling momentum according to boltzmann distribution
    const auto temperature = track.GetVolume()->GetLogicalVolume()->GetMaterial()->GetTemperature();
    muoniumDynamicParticle->SetMomentum(std::sqrt(muonium_mass_c2 * k_Boltzmann * temperature) *
                                        G4ThreeVector(G4RandGauss::shoot(),
                                                      G4RandGauss::shoot(),
                                                      G4RandGauss::shoot()));
    // Pre-assign the decay time
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(muonium_lifetime));
    // Kill the muon, form the (anti-)muonium
    fParticleChange.ProposeTrackStatus(fStopAndKill);
    fParticleChange.AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));
    return std::addressof(fParticleChange);
}

} // namespace MACE::Simulation::Physics::Process
