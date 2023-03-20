namespace MACE::inline Extension::Geant4X::Physics {

inline namespace Messenger {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysicsMessenger;

} // inline namespace Messenger

inline namespace Process {

template<TargetForMuoniumPhysics ATarget>
MuoniumFormation<ATarget>::MuoniumFormation() :
    NonMoveableBase(),
    G4VRestProcess(__func__, fUserDefined),
    fMuonium(gsl::not_null(Muonium::Definition())),
    fAntimuonium(gsl::not_null(Antimuonium::Definition())),
    fTarget(&ATarget::Instance()),
    fRandEng(G4Random::getTheEngine()),
    fFormationProbability(0.65),
    fConversionProbability(0),
    fParticleChange() {
    pParticleChange = &fParticleChange;
    MuoniumPhysicsMessenger<ATarget>::Instance().AssignTo(this);
}

template<TargetForMuoniumPhysics ATarget>
G4bool MuoniumFormation<ATarget>::IsApplicable(const G4ParticleDefinition& particle) {
    return &particle == G4MuonPlus::Definition();
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumFormation<ATarget>::StartTracking(G4Track* track) {
    G4VRestProcess::StartTracking(track);
    // the random engine in use
    fRandEng = gsl::not_null(G4Random::getTheEngine());
}

template<TargetForMuoniumPhysics ATarget>
G4VParticleChange* MuoniumFormation<ATarget>::AtRestDoIt(const G4Track& track, const G4Step&) {
    using namespace PhysicalConstant;

    fParticleChange.Initialize(track);
    // The dynamic particle
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    // Determine whether the transition can be observed
    muoniumDynamicParticle->SetDefinition(fRandEng->flat() < fConversionProbability ? fAntimuonium : fMuonium);
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

template<TargetForMuoniumPhysics ATarget>
G4double MuoniumFormation<ATarget>::GetMeanLifeTime(const G4Track& track, G4ForceCondition*) {
    if (fRandEng->flat() < fFormationProbability and fTarget->Contain(track.GetPosition())) {
        return std::numeric_limits<double>::min();
    } else {
        return std::numeric_limits<double>::max();
    }
}

} // inline namespace Process

} // namespace MACE::inline Extension::Geant4X::Physics
