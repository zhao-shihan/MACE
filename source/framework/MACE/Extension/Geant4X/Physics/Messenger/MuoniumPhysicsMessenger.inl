namespace MACE::inline Extension::Geant4X::Physics::Messenger {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysicsMessenger<ATarget>::MuoniumPhysicsMessenger() :
    Env::Memory::Singleton<MuoniumPhysicsMessenger<ATarget>>(),
    G4UImessenger(),
    fMuoniumFormation(nullptr),
    fMuoniumTransport(nullptr),
    fMuoniumPhysicsDirectory(),
    fFormationProcessDirectory(),
    fSetFormationProbability(),
    fSetConversionProbability(),
    fTransportProcessDirectory(),
    fSetMeanFreePath(),
    fSetManipulateAllSteps() {

    fMuoniumPhysicsDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/");
    fMuoniumPhysicsDirectory->SetGuidance("Physics of muonium and anti-muonium.");

    fFormationProcessDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/Formation/");
    fFormationProcessDirectory->SetGuidance("Muonium formation and transition process.");

    fSetFormationProbability = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumPhysics/Formation/SetFormationProbability", this);
    fSetFormationProbability->SetGuidance("Set integrated probability of rest mu+ captures a e- in the target.");
    fSetFormationProbability->SetParameterName("P", false);
    fSetFormationProbability->AvailableForStates(G4State_Idle);

    fSetConversionProbability = std::make_unique<G4UIcmdWithADouble>("/MACE/Physics/MuoniumPhysics/Formation/SetConversionProbability", this);
    fSetConversionProbability->SetGuidance("Set integrated probability of muonium to anti-muonium conversion.");
    fSetConversionProbability->SetParameterName("P", false);
    fSetConversionProbability->AvailableForStates(G4State_Idle);

    fTransportProcessDirectory = std::make_unique<G4UIdirectory>("/MACE/Physics/MuoniumPhysics/Transport/");
    fTransportProcessDirectory->SetGuidance("The transport process of thermal muonium in the target.");

    fSetMeanFreePath = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Physics/MuoniumPhysics/Transport/SetMeanFreePath", this),
    fSetMeanFreePath->SetGuidance("Set thermal muonium mean free path in the target.");
    fSetMeanFreePath->SetParameterName("lambda", false);
    fSetMeanFreePath->SetUnitCategory("Length");
    fSetMeanFreePath->AvailableForStates(G4State_Idle);

    fSetManipulateAllSteps = std::make_unique<G4UIcmdWithABool>("/MACE/Physics/MuoniumPhysics/Transport/SetManipulateAllSteps", this),
    fSetManipulateAllSteps->SetGuidance("Set whether show each step of thermal random flight of muonium in the target or not.\n"
                                        "Warning: can be time consuming if set to true.");
    fSetManipulateAllSteps->SetParameterName("b", false);
    fSetManipulateAllSteps->AvailableForStates(G4State_Idle);
}

template<TargetForMuoniumPhysics ATarget>
void MuoniumPhysicsMessenger<ATarget>::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetFormationProbability.get()) {
        fMuoniumFormation->SetFormationProbability(fSetFormationProbability->GetNewDoubleValue(value));
    } else if (command == fSetConversionProbability.get()) {
        fMuoniumFormation->SetConversionProbability(fSetConversionProbability->GetNewDoubleValue(value));
    } else if (command == fSetMeanFreePath.get()) {
        fMuoniumTransport->SetMeanFreePath(fSetMeanFreePath->GetNewDoubleValue(value));
    } else if (command == fSetManipulateAllSteps.get()) {
        fMuoniumTransport->SetManipulateAllSteps(fSetManipulateAllSteps->GetNewBoolValue(value));
    }
}

} // namespace MACE::inline Extension::Geant4X::Physics::Messenger
