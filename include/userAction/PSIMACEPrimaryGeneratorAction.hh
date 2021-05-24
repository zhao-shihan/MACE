/*Shoot Muon+ current,
    energy with gaussrandom,
    same momentum derection*/

#ifndef PSIMACEPrimaryGeneratorAction_h
#define PSIMACEPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "messenger/PSIMACEPGAMessenger.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleDefinition;
class PSIMACEPGAMessenger;

// The primary generator action class with particle gun.

class PSIMACEPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
    G4ParticleGun* fParticleGun;
    G4int fNumberOfParticlesPerEvent;

    PSIMACEPGAMessenger* fMessenger;

public:
    PSIMACEPrimaryGeneratorAction(G4int numberOfParticlesPerEvent = 8000);
    virtual ~PSIMACEPrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

    void SetParticlesPerEvent(G4double ppe) { fNumberOfParticlesPerEvent = ppe; }
};

#endif
