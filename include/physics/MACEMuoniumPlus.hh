#ifndef MACEMuoniumPlus_h
#define MACEMuoniumPlus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//Muonium+ Definition

class MACEMuoniumPlus : public G4ParticleDefinition
{
 private:
   static MACEMuoniumPlus* theInstance;
   MACEMuoniumPlus(){}
   ~MACEMuoniumPlus(){}

 public:
   static MACEMuoniumPlus* Definition();
   static MACEMuoniumPlus* MuoniumDefinition();
   static MACEMuoniumPlus* Muonium();
};

#endif

