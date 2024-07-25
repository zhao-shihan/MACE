namespace MACE::inline Simulation::inline Action {

template<typename ADerived>
NeutrinoKillerSteppingAction<ADerived>::NeutrinoKillerSteppingAction() :
    Mustard::Env::Memory::PassiveSingleton<ADerived>{},
    G4UserSteppingAction{},
    fEnableNeutrinoKiller{true},
    fMessengerRegister{static_cast<ADerived*>(this)} {}

template<typename ADerived>
auto NeutrinoKillerSteppingAction<ADerived>::UserSteppingAction(const G4Step* step) -> void {
    if (fEnableNeutrinoKiller) {
        switch (auto& track{*step->GetTrack()};
                muc::abs(track.GetParticleDefinition()->GetPDGEncoding())) {
        case 12:
        case 14:
        case 16:
            track.SetTrackStatus(fStopAndKill);
            SteppingActionForNeutrino(*step);
            return;
        }
    }
    SteppingActionWithoutNeutrino(*step);
}

} // namespace MACE::inline Simulation::inline Action
