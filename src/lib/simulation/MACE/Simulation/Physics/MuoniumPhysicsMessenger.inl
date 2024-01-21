namespace MACE::inline Simulation::inline Physics {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysicsMessenger<ATarget>::MuoniumPhysicsMessenger() :
    Geant4X::SingletonMessenger<MuoniumPhysicsMessenger<ATarget>,
                                MuoniumFormation<ATarget>,
                                MuoniumTransport<ATarget>>{},
    fMuoniumPhysicsDirectory{},
    fFormationProcessDirectory{},
    fFormationProbability{},
    fConversionProbability{},
    fTransportProcessDirectory{},
    fMeanFreePath{},
    fManipulateAllSteps{} {

    fMuoniumPhysicsDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/");
    fMuoniumPhysicsDirectory->SetGuidance("Physics of muonium and anti-muonium.");

    fFormationProcessDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/Formation/");
    fFormationProcessDirectory->SetGuidance("Muonium formation and transition process.");

    fFormationProbability = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumPhysics/Formation/FormationProbability", this);
    fFormationProbability->SetGuidance("Set integrated probability of rest mu+ captures a e- in the target.");
    fFormationProbability->SetParameterName("P", false);
    fFormationProbability->AvailableForStates(G4State_Idle);

    fConversionProbability = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumPhysics/Formation/ConversionProbability", this);
    fConversionProbability->SetGuidance("Set integrated probability of muonium to anti-muonium conversion.");
    fConversionProbability->SetParameterName("P", false);
    fConversionProbability->AvailableForStates(G4State_Idle);

    fTransportProcessDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/Transport/");
    fTransportProcessDirectory->SetGuidance("The transport process of thermal muonium in the target.");

    fMeanFreePath = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuoniumPhysics/Transport/MeanFreePath", this),
    fMeanFreePath->SetGuidance("Set thermal muonium mean free path in the target.");
    fMeanFreePath->SetParameterName("lambda", false);
    fMeanFreePath->SetUnitCategory("Length");
    fMeanFreePath->AvailableForStates(G4State_Idle);

    fManipulateAllSteps = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuoniumPhysics/Transport/ManipulateAllSteps", this),
    fManipulateAllSteps->SetGuidance("Set whether show each step of thermal random flight of muonium in the target or not.\n"
                                     "Warning: can be time consuming if set to true.");
    fManipulateAllSteps->SetParameterName("b", false);
    fManipulateAllSteps->AvailableForStates(G4State_Idle);
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumPhysicsMessenger<ATarget>::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fFormationProbability.get()) {
        this->template Deliver<MuoniumFormation<ATarget>>([&](auto&& r) { r.FormationProbability(fFormationProbability->GetNewDoubleValue(value)); });
    } else if (command == fConversionProbability.get()) {
        this->template Deliver<MuoniumFormation<ATarget>>([&](auto&& r) { r.ConversionProbability(fConversionProbability->GetNewDoubleValue(value)); });
    } else if (command == fMeanFreePath.get()) {
        this->template Deliver<MuoniumTransport<ATarget>>([&](auto&& r) { r.MeanFreePath(fMeanFreePath->GetNewDoubleValue(value)); });
    } else if (command == fManipulateAllSteps.get()) {
        this->template Deliver<MuoniumTransport<ATarget>>([&](auto&& r) { r.ManipulateAllSteps(fManipulateAllSteps->GetNewBoolValue(value)); });
    }
}

} // namespace MACE::inline Simulation::inline Physics
