#include "messenger/PSIMACEPhysicsMessenger.hh"
#include "userAction/PSIMACEDetectorConstruction.hh"
#include "physics/PSIMACEEmStandardPhysics.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

PSIMACEPhysicsMessenger::PSIMACEPhysicsMessenger(PSIMACEEmStandardPhysics* emp)
 : G4UImessenger(),
   //fDetectorConstruction(Det)
   fEmStandardPhysics(emp)
{
//	fDetectorDirectory = new G4UIdirectory("/PSIMACE/");
//	fDetectorDirectory->SetGuidance("Detector construction control.");

	fPhysicsDirectory = new G4UIdirectory("/PSIMACEPhysics/");
	fPhysicsDirectory->SetGuidance("EM PhysicsList control.");

	fRDPhysicsCmd = new G4UIcmdWithADouble("/PSIMACEPhysics/SetMuonRareDecayMode",this);
	fRDPhysicsCmd->SetGuidance("Set the branch ratio of Muon Rare Decay.Parameter 0~1.");
	fRDPhysicsCmd->SetParameterName("branchratio",false);
	fRDPhysicsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fMMCPhysicsCmd = new G4UIcmdWithADouble("/PSIMACEPhysics/SetMuMuConversion",this);
	fMMCPhysicsCmd->SetGuidance("Set the probability of Muonium-AntiMuonium conversion.Parameter 0~1.");
	fMMCPhysicsCmd->SetParameterName("Pofconversion",false);
	fMMCPhysicsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fMFPhysicsCmd = new G4UIcmdWithADouble("/PSIMACEPhysics/SetMuFormation",this);
	fMFPhysicsCmd->SetGuidance("Control the physics process of Muonium Formation.");
	fMFPhysicsCmd->SetParameterName("yields",false);
	fMFPhysicsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

/*	fTSLengthCmd = new G4UIcmdWithADoubleAndUnit("/PSIMACEDetector/SetTransportSysLength",this);
	fTSLengthCmd->SetGuidance("Set the length of second part of Positron transport system.");
	fTSLengthCmd->SetParameterName("Tlength",false);
	fTSLengthCmd->SetUnitCategory("Length");
	fTSLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);*/

}

PSIMACEPhysicsMessenger::~PSIMACEPhysicsMessenger()
{
	delete fRDPhysicsCmd;
	delete fMMCPhysicsCmd;
	delete fMFPhysicsCmd;


//	delete fTSLengthCmd;
}

void PSIMACEPhysicsMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if(command == fRDPhysicsCmd){
	fEmStandardPhysics->SetRDPhysics(fRDPhysicsCmd->GetNewDoubleValue(newValue));}
	//else fEmStandardPhysics->SetRDPhysics( 0. );


	if(command == fMMCPhysicsCmd){
	fEmStandardPhysics->SetMMCPhysics(fMMCPhysicsCmd->GetNewDoubleValue(newValue));}
	//else fEmStandardPhysics->SetMMCPhysics( 0. );


	if(command == fMFPhysicsCmd){
	fEmStandardPhysics->SetMFPhysics(fMFPhysicsCmd->GetNewDoubleValue(newValue));}
	//else fEmStandardPhysics->SetMFPhysics( 1.0 );


//	if(command == fTSLengthCmd){
//	fDetectorConstruction->SetTSLength(fTSLengthCmd->GetNewDoubleValue(newValue));}


}


