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
    fParticleChange(),
    fMeanLifeTime(1.46467_us), // 60%
    fConversionProbability(8.3e-11) {
    // PhysicsMessenger::Instance().Set(this);
}

G4VParticleChange* MuoniumFormation::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);

    G4ParticleDefinition* muonium;
    if (G4UniformRand() < fConversionProbability) {
        muonium = Particle::AntiMuonium::Definition();
    } else {
        muonium = Particle::Muonium::Definition();
    }
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    muoniumDynamicParticle->SetDefinition(muonium);
    const auto temperature = track.GetVolume()->GetLogicalVolume()->GetMaterial()->GetTemperature();
    const auto sigmaP = std::sqrt(muonium_mass_c2 * k_Boltzmann * temperature);
    muoniumDynamicParticle->SetMomentum(G4ThreeVector(G4RandGauss::shoot(0, sigmaP),
                                                      G4RandGauss::shoot(0, sigmaP),
                                                      G4RandGauss::shoot(0, sigmaP)));
    // muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(muonium->GetPDGLifeTime()));

    fParticleChange.AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));
    fParticleChange.ProposeTrackStatus(fStopAndKill);

    return std::addressof(fParticleChange);
}

} // namespace MACE::Simulation::Physics::Process
