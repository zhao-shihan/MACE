#pragma once

#include "G4VUserActionInitialization.hh"

#include "SimG4Global.hh"
#include "detector/DetectorConstruction.hh"

class MACE::SimG4::ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization(const DetectorConstruction* pDetectorConstruction);
    void Build() const override;

private:
    const DetectorConstruction* const fpDetectorConstruction;
};
