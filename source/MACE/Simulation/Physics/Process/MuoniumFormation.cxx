// #include "MACE/Simulation/SimMACE/Messenger/PhysicsMessenger.hxx"
#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4MuonPlus.hh"
#include "G4RunManager.hh"

namespace MACE::Simulation::Physics::Process {

using namespace Utility::LiteralUnit::Time;
using namespace Utility::PhysicalConstant;

MuoniumFormation::MuoniumFormation() :
    G4VRestProcess("MuoniumFormation", fElectromagnetic),
    fTarget(std::addressof(Target::Instance())),
    fMuonium(Particle::Muonium::Definition()),
    fAntiMuonium(Particle::AntiMuonium::Definition()),
    fFormationProbability(0.6),
    fConversionProbability(0),
    fParticleChange() {
    Messenger::MuoniumPhysicsMessenger::Instance().SetTo(this);
}

G4VParticleChange* MuoniumFormation::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    // The dynamic particle
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    // Determine whether the transition can be observed
    muoniumDynamicParticle->SetDefinition(G4UniformRand() < fConversionProbability ? fAntiMuonium : fMuonium);
    // Sampling momentum according to boltzmann distribution
    auto* const randEng = G4Random::getTheEngine();
    const auto temperature = track.GetVolume()->GetLogicalVolume()->GetMaterial()->GetTemperature();
    muoniumDynamicParticle->SetMomentum(std::sqrt(muonium_mass_c2 * k_Boltzmann * temperature) *
                                        G4ThreeVector(G4RandGauss::shoot(randEng),
                                                      G4RandGauss::shoot(randEng),
                                                      G4RandGauss::shoot(randEng)));
    // Pre-assign the decay time for better performance
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(randEng, muonium_lifetime));
    // Kill the muon, form the (anti-)muonium
    fParticleChange.ProposeTrackStatus(fStopAndKill);
    fParticleChange.AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));
    // Clean
    ClearNumberOfInteractionLengthLeft();
    return std::addressof(fParticleChange);
}

G4double MuoniumFormation::GetMeanLifeTime(const G4Track& track, G4ForceCondition*) {
    if (fTarget->Contains(track.GetPosition())) {
        if (G4UniformRand() < fFormationProbability) {
            return 0;
        } else {
            return DBL_MAX;
        }
    } else {
        return DBL_MAX;
    }
}

} // namespace MACE::Simulation::Physics::Process
