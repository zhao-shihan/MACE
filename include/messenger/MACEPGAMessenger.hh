//UICommand for ParticleSource.
#ifndef PGMessenger_h
#define PGMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MACEPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADouble;

class MACEPGAMessenger : public G4UImessenger {
private:
    MACEPrimaryGeneratorAction* fPrimaryGeneratorAction;
    G4UIdirectory* fDirectory;
    G4UIcmdWithADouble* fPPECmd;

public:
    MACEPGAMessenger(MACEPrimaryGeneratorAction*);
    virtual ~MACEPGAMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
};

#endif
