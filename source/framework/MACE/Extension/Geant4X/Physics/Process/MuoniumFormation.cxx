#include "MACE/Extension/Geant4X/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.hxx"
#include "MACE/Extension/Geant4X/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4MuonPlus.hh"

#include "gsl/gsl"

#include <limits>

namespace MACE::inline Extension::Geant4X::Physics::Process {

using namespace LiteralUnit::Time;
using namespace PhysicalConstant;

MuoniumFormation::MuoniumFormation() :
    G4VRestProcess("MuoniumFormation", fUserDefined),
    fMuonium(gsl::not_null(Particle::Muonium::Definition())),
    fAntiMuonium(gsl::not_null(Particle::AntiMuonium::Definition())),
    fTarget(&Target::Instance()),
    fRandEng(G4Random::getTheEngine()),
    fFormationProbability(0.65),
    fConversionProbability(0),
    fParticleChange() {
    pParticleChange = &fParticleChange;
    Messenger::MuoniumPhysicsMessenger::Instance().AssignTo(this);
}

G4bool MuoniumFormation::IsApplicable(const G4ParticleDefinition& particle) {
    return &particle == G4MuonPlus::Definition();
}

void MuoniumFormation::StartTracking(G4Track* track) {
    G4VRestProcess::StartTracking(track);
    // the random engine in use
    fRandEng = gsl::not_null(G4Random::getTheEngine());
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
    return &fParticleChange;
}

G4double MuoniumFormation::GetMeanLifeTime(const G4Track& track, G4ForceCondition*) {
    if (fRandEng->flat() < fFormationProbability and fTarget->Contain(track.GetPosition())) {
        return std::numeric_limits<double>::min();
    } else {
        return std::numeric_limits<double>::max();
    }
}

} // namespace MACE::inline Extension::Geant4X::Physics::Process
