/*Shoot Muon+ current,
    energy with gaussrandom,
    same momentum derection*/

#ifndef MACEPrimaryGeneratorAction_h
#define MACEPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "messenger/MACEPGAMessenger.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleDefinition;
class MACEPGAMessenger;

// The primary generator action class with particle gun.

class MACEPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
    G4ParticleGun* fParticleGun;
    G4int fNumberOfParticlesPerEvent;

    MACEPGAMessenger* fMessenger;

public:
    MACEPrimaryGeneratorAction(G4int numberOfParticlesPerEvent = 8000);
    virtual ~MACEPrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

    void SetParticlesPerEvent(G4double ppe) { fNumberOfParticlesPerEvent = ppe; }
};

#endif
