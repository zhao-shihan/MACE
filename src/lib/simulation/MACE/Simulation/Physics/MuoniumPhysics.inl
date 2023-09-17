namespace MACE::inline Simulation::Physics {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysics<ATarget>::MuoniumPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{__func__} {
    verboseLevel = verbose;
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumPhysics<ATarget>::ConstructParticle() {
    G4MuonPlus::Definition();
    Muonium::Definition();
    Antimuonium::Definition();
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumPhysics<ATarget>::ConstructProcess() {
    auto muoniumFormation = new MuoniumFormation<ATarget>;
    auto muoniumTransport = new MuoniumTransport<ATarget>;

    auto muonPlus = G4MuonPlus::Definition()->GetProcessManager();
    muonPlus->AddRestProcess(muoniumFormation);

    auto muonium = Muonium::Definition()->GetProcessManager();
    muonium->AddContinuousProcess(muoniumTransport);

    auto antiMuonium = Antimuonium::Definition()->GetProcessManager();
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::inline Simulation::Physics
