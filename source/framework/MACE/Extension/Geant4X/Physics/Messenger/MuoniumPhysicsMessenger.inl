namespace MACE::inline Extension::Geant4X::Physics::Messenger {

template<TargetForMuoniumPhysics ATarget>
MuoniumPhysicsMessenger<ATarget>::MuoniumPhysicsMessenger() :
    Env::Memory::Singleton<MuoniumPhysicsMessenger<ATarget>>(),
    G4UImessenger(),
    fMuoniumFormation(nullptr),
    fMuoniumTransport(nullptr),
    fMuoniumPhysicsDirectory(),
    fFormationProcessDirectory(),
    fFormationProbability(),
    fConversionProbability(),
    fTransportProcessDirectory(),
    fMeanFreePath(),
    fManipulateAllSteps() {

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
void MuoniumPhysicsMessenger<ATarget>::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fFormationProbability.get()) {
        fMuoniumFormation->FormationProbability(fFormationProbability->GetNewDoubleValue(value));
    } else if (command == fConversionProbability.get()) {
        fMuoniumFormation->ConversionProbability(fConversionProbability->GetNewDoubleValue(value));
    } else if (command == fMeanFreePath.get()) {
        fMuoniumTransport->MeanFreePath(fMeanFreePath->GetNewDoubleValue(value));
    } else if (command == fManipulateAllSteps.get()) {
        fMuoniumTransport->ManipulateAllSteps(fManipulateAllSteps->GetNewBoolValue(value));
    }
}

} // namespace MACE::inline Extension::Geant4X::Physics::Messenger
