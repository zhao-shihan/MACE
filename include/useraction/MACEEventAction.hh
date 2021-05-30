/*MACE EventAction
    Taking data from SensitiveDetector through hitcollection*/

#ifndef MACEEventAction_h
#define MACEEventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

// Event action class

class MACEEventAction : public G4UserEventAction {
public:
    MACEEventAction();
    virtual ~MACEEventAction();

    virtual void  BeginOfEventAction(const G4Event*);
    virtual void    EndOfEventAction(const G4Event*);
};


#endif
