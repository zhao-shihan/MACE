namespace MACE::inline Extension::Geant4X::Physics {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysics<ATarget>::MuoniumPhysics(G4int verbose) :
    NonMoveableBase(),
    G4VPhysicsConstructor(__func__) {
    verboseLevel = verbose;
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumPhysics<ATarget>::ConstructParticle() {
    G4MuonPlus::Definition();
    Particle::Muonium::Definition();
    Particle::AntiMuonium::Definition();
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumPhysics<ATarget>::ConstructProcess() {
    auto muoniumFormation = new Process::MuoniumFormation<ATarget>;
    auto muoniumTransport = new Process::MuoniumTransport<ATarget>;

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumFormation);

    auto muonium = Particle::Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = Particle::AntiMuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::inline Extension::Geant4X::Physics
