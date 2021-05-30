// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      July 2020 Yuzhe.M
//
//	  mu+ decay with inner Bremsstrahlung
// ------------------------------------------------------------
#ifndef MACEMuonDecayChannel_h
#define MACEMuonDecayChannel_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VDecayChannel.hh"

class MACEMuonDecayChannel :public G4VDecayChannel
{
  // Class Decription
  //  This class describes muon decay kinemtics.
  //  This version neglects muon polarization  
  //              assumes the pure V-A coupling
  //              gives incorrect energy spectrum for neutrinos
  //

  public:  // With Description
    //Constructors 
      MACEMuonDecayChannel(const G4String& theParentName,
			 G4double        theBR);
    //  Destructor
      virtual ~MACEMuonDecayChannel();

  protected:
    // Copy constructor and assignment operator
      MACEMuonDecayChannel(const MACEMuonDecayChannel &);
      MACEMuonDecayChannel & operator=(const MACEMuonDecayChannel &);

  protected:
      MACEMuonDecayChannel();

  public:  // With Description
     virtual G4DecayProducts *DecayIt(G4double);     
  
};  


#endif
