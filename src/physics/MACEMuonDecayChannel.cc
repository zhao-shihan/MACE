#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4DecayProducts.hh"
#include "G4VDecayChannel.hh"
#include "physics/MACEMuonDecayChannel.hh"
#include "Randomize.hh"
#include "G4LorentzVector.hh"
#include "G4LorentzRotation.hh"
#include "G4RotationMatrix.hh"

MACEMuonDecayChannel::MACEMuonDecayChannel()
                   :G4VDecayChannel()
{
}

MACEMuonDecayChannel::MACEMuonDecayChannel(const G4String& theParentName, 
				       G4double        theBR)
                   :G4VDecayChannel("Muon Decay",1)
{
  // set names for daughter particles
  if (theParentName == "mu+") {
    SetBR(theBR);
    SetParent("mu+");
    SetNumberOfDaughters(5);
    SetDaughter(0, "e+");
    SetDaughter(1, "nu_e");
    SetDaughter(2, "anti_nu_mu");
    SetDaughter(3, "e-");
    SetDaughter(4, "e+");
  } else if (theParentName == "mu-") {
    SetBR(theBR);
    SetParent("mu-");
    SetNumberOfDaughters(5);
    SetDaughter(0, "e-");
    SetDaughter(1, "anti_nu_e");
    SetDaughter(2, "nu_mu");
    SetDaughter(3, "e+");
    SetDaughter(4, "e-");
  } else {
#ifdef G4VERBOSE
    if (GetVerboseLevel()>0) {
      G4cout << "MACEMuonDecayChannel:: constructor :";
      G4cout << " parent particle is not muon but ";
      G4cout << theParentName << G4endl;
    }
#endif
  }
}

MACEMuonDecayChannel::MACEMuonDecayChannel(const MACEMuonDecayChannel &right):
  G4VDecayChannel(right)
{
}

MACEMuonDecayChannel::~MACEMuonDecayChannel()
{
}

MACEMuonDecayChannel & MACEMuonDecayChannel::operator=(const MACEMuonDecayChannel & right)
{
  if (this != &right) { 
    kinematics_name = right.kinematics_name;
    verboseLevel = right.verboseLevel;
    rbranch = right.rbranch;

    // copy parent name
    parent_name = new G4String(*right.parent_name);

    // clear daughters_name array
    ClearDaughtersName();

    // recreate array
    numberOfDaughters = right.numberOfDaughters;
    if ( numberOfDaughters >0 ) {
      if (daughters_name !=0) ClearDaughtersName();
      daughters_name = new G4String*[numberOfDaughters];
      //copy daughters name
      for (G4int index=0; index < numberOfDaughters; index++) {
          daughters_name[index] = new G4String(*right.daughters_name[index]);
      }
    }
  }
  return *this;
}

G4DecayProducts *MACEMuonDecayChannel::DecayIt(G4double) 
{
  // this version neglects muon polarization,and electron mass  
  //              assumes the pure V-A coupling
  //              the Neutrinos are correctly V-A. 
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) G4cout << "MACEMuonDecayChannel::DecayIt ";
#endif

  CheckAndFillParent();
  CheckAndFillDaughters();
 
  // parent mass
  // e+e- pair calculate independently
  G4double parentmass = G4MT_parent->GetPDGMass();
  G4double bseed;
  // e+e- pair take some energy
  for(G4int loop0 = 0; loop0 < 10; ++loop0)
  {
  bseed = G4UniformRand();
  if(bseed > 0.050 && bseed < 0.950)
  {
	loop0 +=10;
	parentmass = bseed *parentmass;
  }
  }

  const int N_DAUGHTER=3;

  //daughters'mass
  G4double daughtermass[N_DAUGHTER]; 
  G4double sumofdaughtermass = 0.0;
  for (G4int index=0; index<N_DAUGHTER; index++){
    daughtermass[index] = G4MT_daughters[index]->GetPDGMass();
    sumofdaughtermass += daughtermass[index];
  }

   //create parent G4DynamicParticle at rest
  G4ThreeVector dummy;
  G4DynamicParticle * parentparticle = new G4DynamicParticle( G4MT_parent, dummy, 0.0);
  //create G4Decayproducts
  G4DecayProducts *products = new G4DecayProducts(*parentparticle);
  delete parentparticle;

  // calculate daughter momentum
  G4double daughtermomentum[N_DAUGHTER];
    // calcurate electron energy
  G4double xmax = (1.0+daughtermass[0]*daughtermass[0]/parentmass/parentmass);
  G4double x;
  
  G4double Ee,Ene;
  
  G4double gam;
  G4double EMax=parentmass/2-daughtermass[0];
  
  const size_t MAX_LOOP=1000;
   //Generating Random Energy
  for (size_t loop1=0; loop1 <MAX_LOOP; ++loop1){
    Ee=G4UniformRand();
    for (size_t loop2 =0; loop2<MAX_LOOP; ++loop2){
      x=xmax*G4UniformRand();
      gam=G4UniformRand();
      if (gam <= x*(1.-x)) break;
      x = xmax;
    }
    Ene=x;
    if ( Ene >= (1.-Ee)) break;
    Ene = 1.-Ee;
  }
  G4double Enm=(2.-Ee-Ene);


 //initialisation of rotation parameters

  G4double costheta,sintheta,rphi,rtheta,rMACE;
  costheta= 1.-2./Ee-2./Ene+2./Ene/Ee;
  sintheta=sqrt(1.-costheta*costheta);
  

  rphi=twopi*G4UniformRand()*rad;
  rtheta=(std::acos(2.*G4UniformRand()-1.));
  rMACE=twopi*G4UniformRand()*rad;

  G4RotationMatrix rot;
  rot.set(rphi,rtheta,rMACE);

  //electron 0
  daughtermomentum[0]=sqrt(Ee*Ee*EMax*EMax+2.0*Ee*EMax * daughtermass[0]);
  G4ThreeVector direction0(0.0,0.0,1.0);

  direction0 *= rot;

  G4DynamicParticle * daughterparticle = new G4DynamicParticle ( G4MT_daughters[0],	 direction0 * daughtermomentum[0]);

  products->PushProducts(daughterparticle);
  //electronic neutrino  1

  daughtermomentum[1]=sqrt(Ene*Ene*EMax*EMax+2.0*Ene*EMax * daughtermass[1]);
  G4ThreeVector direction1(sintheta,0.0,costheta);

  direction1 *= rot;

  G4DynamicParticle * daughterparticle1 = new G4DynamicParticle ( G4MT_daughters[1],	 direction1 * daughtermomentum[1]);
  products->PushProducts(daughterparticle1);

  //muonnic neutrino 2
  
     daughtermomentum[2]=sqrt(Enm*Enm*EMax*EMax +2.0*Enm*EMax*daughtermass[2]);
  G4ThreeVector direction2(-Ene/Enm*sintheta,0,-Ee/Enm-Ene/Enm*costheta);

  direction2 *= rot;

  G4DynamicParticle * daughterparticle2 = new G4DynamicParticle ( G4MT_daughters[2],
	 direction2 * daughtermomentum[2]);
  products->PushProducts(daughterparticle2);

  // e+e- pair
  //Set Direction
  G4double theta3 = 360.0*G4UniformRand()*deg;
  G4double phi3   = (180.0*G4UniformRand()-90.0)*deg;
  G4ThreeVector direction3(cos(phi3)*sin(theta3),cos(phi3)*cos(theta3), sin(phi3));
  G4double pairEk = (1.0-bseed)*parentmass/bseed/2-daughtermass[0];

  G4DynamicParticle * daughterparticle3 = new G4DynamicParticle ( G4MT_daughters[3],
	 direction3 , pairEk );
  products->PushProducts(daughterparticle3);

  G4DynamicParticle * daughterparticle4 = new G4DynamicParticle ( G4MT_daughters[4],
	 -direction3 , pairEk );
  products->PushProducts(daughterparticle4);
  

 // output message
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) {
    G4cout << "MACEMuonDecayChannel::DecayIt ";
    G4cout << "  create decay products in rest frame " <<G4endl;
    products->DumpInfo();
  }
#endif
  return products;
}
