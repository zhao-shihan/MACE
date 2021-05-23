/*PSIMACE EventAction
    Taking data from SensitiveDetector through hitcollection*/

#ifndef PSIMACEEventAction_h
#define PSIMACEEventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

// Event action class

class PSIMACEEventAction : public G4UserEventAction {
public:
    PSIMACEEventAction();
    virtual ~PSIMACEEventAction();

    virtual void  BeginOfEventAction(const G4Event*);
    virtual void    EndOfEventAction(const G4Event*);
};


#endif
