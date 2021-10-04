#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimG4Global.hh"
#include "detector/DetectorConstruction.hh"

class MACE::SimG4::ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    void Build() const override;
};
