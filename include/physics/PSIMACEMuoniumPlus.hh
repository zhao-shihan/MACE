#ifndef PSIMACEMuoniumPlus_h
#define PSIMACEMuoniumPlus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//Muonium+ Definition

class PSIMACEMuoniumPlus : public G4ParticleDefinition
{
 private:
   static PSIMACEMuoniumPlus* theInstance;
   PSIMACEMuoniumPlus(){}
   ~PSIMACEMuoniumPlus(){}

 public:
   static PSIMACEMuoniumPlus* Definition();
   static PSIMACEMuoniumPlus* MuoniumDefinition();
   static PSIMACEMuoniumPlus* Muonium();
};

#endif

