#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Action::ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    void Build() const override;
};
