namespace MACE::inline Simulation::inline Action {

template<typename ADerived>
NeutrinoKillerSteppingAction<ADerived>::NeutrinoKillerSteppingAction() :
    Mustard::Env::Memory::PassiveSingleton<ADerived>{},
    G4UserSteppingAction{},
    fEnableNeutrinoKiller{true},
    fMessengerRegister{static_cast<ADerived*>(this)} {}

template<typename ADerived>
auto NeutrinoKillerSteppingAction<ADerived>::EnableNeutrinoKiller(bool val) -> void {
    fEnableNeutrinoKiller = val;
    auto SetPhysicalProcessActivation{
        [&, processTable = G4ProcessTable::GetProcessTable()](auto&& particle) {
            processTable->SetProcessActivation(fElectromagnetic, particle, not val);
            processTable->SetProcessActivation(fOptical, particle, not val);
            processTable->SetProcessActivation(fHadronic, particle, not val);
            processTable->SetProcessActivation(fPhotolepton_hadron, particle, not val);
            processTable->SetProcessActivation(fDecay, particle, not val);
            processTable->SetProcessActivation(fGeneral, particle, not val);
            processTable->SetProcessActivation(fParameterisation, particle, not val);
            processTable->SetProcessActivation(fPhonon, particle, not val);
            processTable->SetProcessActivation(fUCN, particle, not val);
        }};
    SetPhysicalProcessActivation(G4NeutrinoE::Definition());
    SetPhysicalProcessActivation(G4AntiNeutrinoE::Definition());
    SetPhysicalProcessActivation(G4NeutrinoMu::Definition());
    SetPhysicalProcessActivation(G4AntiNeutrinoMu::Definition());
    SetPhysicalProcessActivation(G4NeutrinoTau::Definition());
    SetPhysicalProcessActivation(G4AntiNeutrinoTau::Definition());
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}

template<typename ADerived>
auto NeutrinoKillerSteppingAction<ADerived>::UserSteppingAction(const G4Step* step) -> void {
    if (fEnableNeutrinoKiller) {
        switch (auto& track{*step->GetTrack()};
                muc::abs(track.GetParticleDefinition()->GetPDGEncoding())) {
        case 12:
        case 14:
        case 16:
            track.SetTrackStatus(fKillTrackAndSecondaries);
            SteppingActionForNeutrino(*step);
            return;
        }
    }
    SteppingActionWithoutNeutrino(*step);
}

} // namespace MACE::inline Simulation::inline Action
