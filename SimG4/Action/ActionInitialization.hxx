#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimG4/Global.hxx"

class MACE::SimG4::Action::ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    void Build() const override;
};
