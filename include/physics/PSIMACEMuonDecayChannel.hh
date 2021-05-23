// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      July 2020 Yuzhe.M
//
//	  mu+ decay with inner Bremsstrahlung
// ------------------------------------------------------------
#ifndef PSIMACEMuonDecayChannel_h
#define PSIMACEMuonDecayChannel_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VDecayChannel.hh"

class PSIMACEMuonDecayChannel :public G4VDecayChannel
{
  // Class Decription
  //  This class describes muon decay kinemtics.
  //  This version neglects muon polarization  
  //              assumes the pure V-A coupling
  //              gives incorrect energy spectrum for neutrinos
  //

  public:  // With Description
    //Constructors 
      PSIMACEMuonDecayChannel(const G4String& theParentName,
			 G4double        theBR);
    //  Destructor
      virtual ~PSIMACEMuonDecayChannel();

  protected:
    // Copy constructor and assignment operator
      PSIMACEMuonDecayChannel(const PSIMACEMuonDecayChannel &);
      PSIMACEMuonDecayChannel & operator=(const PSIMACEMuonDecayChannel &);

  protected:
      PSIMACEMuonDecayChannel();

  public:  // With Description
     virtual G4DecayProducts *DecayIt(G4double);     
  
};  


#endif
