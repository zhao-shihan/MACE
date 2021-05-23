//UICommand for RunAction.
#ifndef PSIMACERunMessenger_h
#define PSIMACERunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PSIMACERunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class PSIMACERunMessenger : public G4UImessenger {
public:
    PSIMACERunMessenger(PSIMACERunAction*);
    virtual ~PSIMACERunMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    PSIMACERunAction* fRunAction;

    G4UIdirectory* fDirectory;

    G4UIcmdWithAString* fRootcmd; //set file name of .root

};

#endif
