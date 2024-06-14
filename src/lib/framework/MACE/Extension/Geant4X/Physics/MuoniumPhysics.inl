namespace MACE::inline Extension::Geant4X::inline Physics {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysics<ATarget>::MuoniumPhysics(G4int verbose) :
    NonMoveableBase{},
    G4VPhysicsConstructor{"MuoniumPhysics"} {
    verboseLevel = verbose;
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumPhysics<ATarget>::ConstructParticle() -> void {
    G4EmBuilder::ConstructMinimalEmSet();
    G4MuonPlus::Definition();
    Geant4X::Muonium::Definition();
    Geant4X::Antimuonium::Definition();
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumPhysics<ATarget>::ConstructProcess() -> void {
    const auto muoniumFormation{new MuoniumFormation<ATarget>};
    const auto muoniumTransport{new MuoniumTransport<ATarget>};

    const auto muonPlus{G4MuonPlus::Definition()->GetProcessManager()};
    muonPlus->AddRestProcess(muoniumFormation);

    const auto muonium{Geant4X::Muonium::Definition()->GetProcessManager()};
    muonium->AddContinuousProcess(muoniumTransport);

    const auto antiMuonium{Geant4X::Antimuonium::Definition()->GetProcessManager()};
    antiMuonium->AddContinuousProcess(muoniumTransport);
}

} // namespace MACE::inline Extension::Geant4X::inline Physics
