#ifndef MACERunAction_h
#define MACERunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "messenger/MACERunMessenger.hh"
#include "useraction/MACEEventAction.hh"

class MACERunAction : public G4UserRunAction {
private:
    MACERunMessenger* fMessenger;

public:
    MACERunAction();
    virtual ~MACERunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif
