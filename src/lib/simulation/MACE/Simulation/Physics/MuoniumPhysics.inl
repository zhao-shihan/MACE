namespace MACE::inline Simulation::inline Physics {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysics<ATarget>::MuoniumPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuoniumPhysics"} {
    verboseLevel = verbose;
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumPhysics<ATarget>::ConstructParticle() -> void {
    G4MuonPlus::Definition();
    Muonium::Definition();
    Antimuonium::Definition();
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumPhysics<ATarget>::ConstructProcess() -> void {
    auto muoniumFormation = new MuoniumFormation<ATarget>;
    auto muoniumTransport = new MuoniumTransport<ATarget>;

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumFormation);

    auto muonium = Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = Antimuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::inline Simulation::inline Physics
