namespace MACE::inline Simulation::inline Physics::inline Process {

template<TargetForMuoniumPhysics ATarget>
MuoniumFormation<ATarget>::MuoniumFormation() :
    NonMoveableBase{},
    G4VRestProcess{"MuoniumFormation", fUserDefined},
    fFormationProbability{0.655},
    fConversionProbability{0},
    fParticleChange{},
    fMessengerRegister{this} {
    pParticleChange = &fParticleChange;
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumFormation<ATarget>::IsApplicable(const G4ParticleDefinition& particle) -> G4bool {
    return &particle == G4MuonPlus::Definition();
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumFormation<ATarget>::AtRestDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* {
    using namespace PhysicalConstant;
    auto& rng{*G4Random::getTheEngine()};

    fParticleChange.Initialize(track);
    // The dynamic particle
    auto muoniumDynamicParticle = new G4DynamicParticle(*track.GetDynamicParticle());
    // Determine whether the transition can be observed
    muoniumDynamicParticle->SetDefinition(rng.flat() < fConversionProbability ? static_cast<G4ParticleDefinition*>(Antimuonium::Definition()) :
                                                                                static_cast<G4ParticleDefinition*>(Muonium::Definition()));
    // Sampling momentum according to boltzmann distribution
    const auto temperature{track.GetVolume()->GetLogicalVolume()->GetMaterial()->GetTemperature()}; // clang-format off
    const auto momentum{std::sqrt(muonium_mass_c2 * k_Boltzmann * temperature) *
                        G4ThreeVector{G4RandGauss::shoot(&rng),
                                      G4RandGauss::shoot(&rng),
                                      G4RandGauss::shoot(&rng)}}; // clang-format on
    // Set momentum and energy
    muoniumDynamicParticle->SetMomentum(momentum);
    muoniumDynamicParticle->SetKineticEnergy(momentum.mag2() / (2 * muonium_mass_c2));
    // Must pre-assign the decay time to ensure correct behaviour of transport and decay
    // (transport process use this to determine when to stop flight,
    //  instead of relying on G4 tracking mechanism. See MuoniumTransport process for detail.)
    muoniumDynamicParticle->SetPreAssignedDecayProperTime(G4RandExponential::shoot(&rng, muonium_lifetime));
    // Kill the muon, form the (anti-)muonium
    fParticleChange.ProposeTrackStatus(fStopAndKill);
    fParticleChange.AddSecondary(new G4Track{muoniumDynamicParticle, track.GetGlobalTime(), track.GetPosition()});
    // Clean
    ClearNumberOfInteractionLengthLeft();
    return &fParticleChange;
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumFormation<ATarget>::GetMeanLifeTime(const G4Track& track, G4ForceCondition*) -> G4double {
    if (G4Random::getTheEngine()->flat() < fFormationProbability and
        ATarget::Instance().Contain(track.GetPosition())) {
        return std::numeric_limits<double>::min();
    } else {
        return std::numeric_limits<double>::max();
    }
}

} // namespace MACE::inline Simulation::inline Physics::inline Process
