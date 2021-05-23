// ClassName:   G4EmStandardPhysics
//
// Author:      V.Ivanchenko 09.11.2005
//
// Modified:	Yuzhe Mao 04.2020
#include "messenger/PSIMACEPhysicsMessenger.hh"
#include "G4GenericMessenger.hh"
#include "G4ProcessManager.hh"

#include "physics/PSIMACEEmStandardPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4EmParameters.hh"
#include "G4LossTableManager.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4UrbanMscModel.hh"
#include "G4ParticleTypes.hh"


#include "G4MuBremsstrahlungModel.hh"
#include "G4MuPairProductionModel.hh"
#include "G4hBremsstrahlungModel.hh"
#include "G4hPairProductionModel.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4MuIonisation.hh"	

#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4alphaIonisation.hh"
#include "G4eplusAnnihilation.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4MuonPlus.hh"

#include "G4MuonMinus.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4KaonPlus.hh"
#include "G4KaonMinus.hh"
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

#include "physics/PSIMACEMuoniumPlus.hh"	
#include "physics/PSIMACEMuFormation.hh"
#include "physics/PSIMACEMuScatter.hh"
#include "physics/MuDecayChannel.hh"
#include "physics/MuDecayChannelWithSpin.hh"

#include "G4DecayTable.hh"

#include "G4MuonDecayChannel.hh"
#include "physics/PSIMACEMuonDecayChannel.hh"
//#include "G4MuonDecayChannelWithSpin.hh"

#include "G4MuonRadiativeDecayChannelWithSpin.hh"
#include "G4RadioactiveDecay.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4MuonMinusCapture.hh"
#include "G4Decay.hh"

#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4EmModelActivator.hh"
#include "G4GammaGeneralProcess.hh"
// factory
#include "G4PhysicsConstructorFactory.hh"

G4_DECLARE_PHYSCONSTR_FACTORY(PSIMACEEmStandardPhysics);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PSIMACEEmStandardPhysics::PSIMACEEmStandardPhysics(G4int ver, const G4String&)
  : G4VPhysicsConstructor("G4EmStandard"), verbose(ver),
  yields(1.0)
{
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();
  param->SetVerbose(verbose);
  param->SetMinEnergy(1*eV);
  param->SetLowestElectronEnergy(1*eV);
  SetPhysicsType(bElectromagnetic);
}


PSIMACEEmStandardPhysics::~PSIMACEEmStandardPhysics()
{
  delete fmessenger;
}


void PSIMACEEmStandardPhysics::ConstructParticle()
{
  // gamma
  G4Gamma::Gamma();

  // leptons
  G4Electron::Electron();
  G4Positron::Positron();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  PSIMACEMuoniumPlus::MuoniumDefinition();


  // mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();

  // barions
  G4Proton::Proton();
  G4AntiProton::AntiProton();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // ions
  G4Deuteron::Deuteron();
  G4Triton::Triton();
  G4He3::He3();
  G4Alpha::Alpha();
  G4GenericIon::GenericIonDefinition();
}


void PSIMACEEmStandardPhysics::ConstructProcess()
{
  fmessenger = new PSIMACEPhysicsMessenger(this); 
  G4LossTableManager* man = G4LossTableManager::Instance();

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();


  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4String particleType = particle->GetParticleType();
    G4double charge = particle->GetPDGCharge();
    
    if (particleName == "gamma") 
      {
	//gamma
	G4RayleighScattering* theRayleigh = new G4RayleighScattering();
	pmanager->AddDiscreteProcess(theRayleigh);

	G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
	thePhotoElectricEffect->SetEmModel(new G4LivermorePhotoElectricModel());
	pmanager->AddDiscreteProcess(thePhotoElectricEffect);
	
	G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
	theComptonScattering->SetEmModel(new G4LivermoreComptonModel());
	pmanager->AddDiscreteProcess(theComptonScattering);
	
	G4GammaConversion* theGammaConversion = new G4GammaConversion();
	theGammaConversion->SetEmModel(new G4LivermoreGammaConversionModel());
	pmanager->AddDiscreteProcess(theGammaConversion);

      } 

    else if (particleName == "e-") 
      {
	//electron
	// process ordering: AddProcess(name, at rest, along step, post step)
	G4eMultipleScattering* msc = new G4eMultipleScattering();
	msc->SetStepLimitType(fUseDistanceToBoundary);
	pmanager->AddProcess(msc,-1, 1, -1);

	G4eIonisation* eIonisation = new G4eIonisation();
	eIonisation->SetEmModel(new G4LivermoreIonisationModel());
	//eIonisation->SetStepFunction(0.2, 100*um); //improved precision in tracking  
	pmanager->AddProcess(eIonisation,-1, 2, 2);
	
	G4eBremsstrahlung* eBremsstrahlung = new G4eBremsstrahlung();
	eBremsstrahlung->SetEmModel(new G4LivermoreBremsstrahlungModel());
	pmanager->AddProcess(eBremsstrahlung, -1,-3, 3);
      } 
    else if (particleName == "e+") 
      {
	//positron	
	G4eMultipleScattering* msc = new G4eMultipleScattering();
	msc->SetStepLimitType(fUseDistanceToBoundary);
	pmanager->AddProcess(msc,-1, 1, 1);
	
	G4eIonisation* eIonisationP = new G4eIonisation();
	eIonisationP->SetStepFunction(0.2, 100*um); //     
	pmanager->AddProcess(eIonisationP,                 -1, 2, 2);

	//Bremsstrahlung (use default, no low-energy available)
	pmanager->AddProcess(new G4eBremsstrahlung(), -1,-1, 3);

	pmanager->AddProcess(new G4eplusAnnihilation(),0,-1, 4);      
      } 

    else if( particleName == "mu+" || 
	     particleName == "mu-"    ) 
	{
	//muon  
	pmanager->AddProcess(new G4eMultipleScattering,           -1, 1, 1);
	pmanager->AddProcess(new G4MuIonisation(),          -1, 2, 2);
	pmanager->AddProcess(new G4MuBremsstrahlung(),      -1,-1, 3);
	pmanager->AddProcess(new G4MuPairProduction(),      -1,-1, 4);


	if( particleName == "mu-" )
	  pmanager->AddProcess(new G4MuonMinusCapture(), 0,-1,-1);

	//  Muonium Formation process, only for mu+ with energy > 0.5keV.
	//  If the ording parameter is not specified, the process is
      //  added at the end of List of process vectors.
	if( particleName == "mu+" )
	  pmanager->AddDiscreteProcess(new PSIMACEMuFormation());
	} 

    else if (particleName=="Mu") {
      G4VProcess* aMuScatt = new PSIMACEMuScatter();
      pmanager->AddProcess(aMuScatt);
      pmanager->SetProcessOrdering(aMuScatt, idxPostStep, 1);

      G4Decay* theDecayProcess = new G4Decay();
      //musrDecayWithSpin* theDecayProcess = new musrDecayWithSpin();
      pmanager->AddProcess(theDecayProcess);
      pmanager->SetProcessOrderingToLast(theDecayProcess, idxAtRest);
      pmanager->SetProcessOrdering(theDecayProcess, idxPostStep);
    }

    else if (particleName == "proton" || 
	     particleName == "pi+" || 
	     particleName == "pi-")
      {
	pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      
	G4hIonisation* hIonisation = new G4hIonisation();
	hIonisation->SetStepFunction(0.2, 50*um);
	pmanager->AddProcess(hIonisation,                     -1, 2, 2);      
	
	pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
      }
    else if(particleName == "alpha"      ||
	     particleName == "deuteron"   ||
	     particleName == "triton"     ||
	     particleName == "He3")
      {
	pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
	
	G4ionIonisation* ionIoni = new G4ionIonisation();
	ionIoni->SetStepFunction(0.1, 20*um);
	pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      }
    else if (particleName == "GenericIon")
      {
	// OBJECT may be dynamically created as either a GenericIon or nucleus
	// G4Nucleus exists and therefore has particle type nucleus
	
	pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);

	G4ionIonisation* ionIoni = new G4ionIonisation();
	ionIoni->SetEmModel(new G4IonParametrisedLossModel());
	ionIoni->SetStepFunction(0.1, 20*um);
	pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      } 

    else if ((!particle->IsShortLived()) &&
	     (charge != 0.0) && 
	     (particle->GetParticleName() != "chargedgeantino")) 
      {
	//all others charged particles except geantino
        G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
        G4hIonisation* ahadronIon = new G4hIonisation();
	
	pmanager->AddProcess(aMultipleScattering,-1,1,1);

	pmanager->AddProcess(ahadronIon,       -1,2,2);      
      }
    
  }

  // Deexcitation
  man->SetAtomDeexcitation(new G4UAtomicDeexcitation());

  G4EmModelActivator mact(GetPhysicsName());
}

void PSIMACEEmStandardPhysics::SetMMCPhysics(G4double pof)
{
  if( pof <= 1.0 && pof >= 0.)
	{
	G4DecayTable* MuoniumDecayTable = new G4DecayTable();
	MuDecayChannel* mude = new MuDecayChannel("Mu",1.00);
	mude->SetMuMuConversion(pof);
	MuoniumDecayTable -> Insert(mude);
	PSIMACEMuoniumPlus::MuoniumDefinition() -> SetDecayTable(MuoniumDecayTable);
	}
}


void PSIMACEEmStandardPhysics::SetRDPhysics(G4double mbr)
{
  if( mbr <= 1.0 && mbr >= 0.)
	{
	G4DecayTable* MuonPlusDecayTable = new G4DecayTable();
	MuonPlusDecayTable -> Insert(new G4MuonDecayChannel("mu+",1.0-mbr) );
	MuonPlusDecayTable -> Insert(new PSIMACEMuonDecayChannel("mu+",mbr) );// PDG: branch ratio = 3.4e-5
	G4MuonPlus::MuonPlusDefinition() -> SetDecayTable(MuonPlusDecayTable);
	}

}

void PSIMACEEmStandardPhysics::SetMFPhysics(G4double mf)
{
   G4ParticleDefinition *particle = G4MuonPlus::MuonPlusDefinition();
   G4ProcessManager* pmanager = particle->GetProcessManager();
   if(mf == 1.0)
   pmanager->AddDiscreteProcess(new PSIMACEMuFormation());

}
