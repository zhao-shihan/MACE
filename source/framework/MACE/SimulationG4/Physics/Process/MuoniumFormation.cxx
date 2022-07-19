#include "MACE/SimulationG4/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/SimulationG4/Physics/Particle/AntiMuonium.hxx"
#include "MACE/SimulationG4/Physics/Particle/Muonium.hxx"
#include "MACE/SimulationG4/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4MuonPlus.hh"

namespace MACE::SimulationG4::Physics::Process {

using namespace Utility::LiteralUnit::Time;
using namespace Utility::PhysicalConstant;

MuoniumFormation::MuoniumFormation() :
    G4VRestProcess("MuoniumFormation", fUserDefined),
    fTarget(std::addressof(Target::Instance())),
    fMuonium(Particle::Muonium::Definition()),
    fAntiMuonium(Particle::AntiMuonium::Definition()),
    fRandEng(G4Random::getTheEngine()),
    fFormationProbability(0.6),
    fConversionProbability(0),
    fParticleChange() {
    pParticleChange = std::addressof(fParticleChange);
    Messenger::MuoniumPhysicsMessenger::Instance().SetTo(this);
}

G4bool MuoniumFormation::IsApplicable(const G4ParticleDefinition& particle) {
    return std::addressof(particle) == G4MuonPlus::Definition();
}

void MuoniumFormation::StartTracking(G4Track* track) {
    G4VRestProcess::StartTracking(track);
    // the random engine in use
    fRandEng = G4Random::getTheEngine();
}

G4VParticleChange* MuoniumFormation::AtRestDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    // The dynamic particle
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    // Determine whether the transition can be observed
    muoniumDynamicParticle->SetDefinition(fRandEng->flat() < fConversionProbability ? fAntiMuonium : fMuonium);
    // Sampling momentum according to boltzmann distribution
    const auto temperature = track.GetVolume()->GetLogicalVolume()->GetMaterial()->GetTemperature();
    const auto momentum = std::sqrt(muonium_mass_c2 * k_Boltzmann * temperature) *
                          G4ThreeVector(G4RandGauss::shoot(fRandEng),
                                        G4RandGauss::shoot(fRandEng),
                                        G4RandGauss::shoot(fRandEng));
    // Set momentum and energy
    muoniumDynamicParticle->SetMomentum(momentum);
    muoniumDynamicParticle->SetKineticEnergy(momentum.mag2() / (2 * muonium_mass_c2));
    // Must pre-assign the decay time to ensure correct behaviour of transport and decay
    // (transport process use this to determine when to stop flight,
    //  instead of relying on G4 tracking mechanism. See MuoniumTransport process for detail.)
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(fRandEng, muonium_lifetime));
    // Kill the muon, form the (anti-)muonium
    fParticleChange.ProposeTrackStatus(fStopAndKill);
    fParticleChange.AddSecondary(new G4Track(muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()));
    // Clean
    ClearNumberOfInteractionLengthLeft();
    return std::addressof(fParticleChange);
}

G4double MuoniumFormation::GetMeanLifeTime(const G4Track& track, G4ForceCondition*) {
    if (fRandEng->flat() < fFormationProbability) {
        return fTarget->Contains(track.GetPosition()) ? DBL_MIN : DBL_MAX;
    } else {
        return DBL_MAX;
    }
}

} // namespace MACE::Simulation::Physics::Process
