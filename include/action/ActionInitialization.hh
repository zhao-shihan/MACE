#pragma once

#include "MACEGlobal.hh"
#include "G4VUserActionInitialization.hh"

class MACE::ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    virtual void Build() const;
};
