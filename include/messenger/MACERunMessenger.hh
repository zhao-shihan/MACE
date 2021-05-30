//UICommand for RunAction.
#ifndef MACERunMessenger_h
#define MACERunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MACERunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class MACERunMessenger : public G4UImessenger {
public:
    MACERunMessenger(MACERunAction*);
    virtual ~MACERunMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    MACERunAction* fRunAction;

    G4UIdirectory* fDirectory;

    G4UIcmdWithAString* fRootcmd; //set file name of .root

};

#endif
