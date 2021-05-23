#ifndef PSIMACERunAction_h
#define PSIMACERunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "messenger/PSIMACERunMessenger.hh"
#include "userAction/PSIMACEEventAction.hh"

class PSIMACERunAction : public G4UserRunAction {
private:
    PSIMACERunMessenger* fMessenger;

public:
    PSIMACERunAction();
    virtual ~PSIMACERunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif
