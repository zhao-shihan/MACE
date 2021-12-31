#pragma once

#include "SimG4/Global.hxx"
#include "G4ParticleDefinition.hh"

// AntiMuonium Definition

class MACE::SimG4::Physics::AntiMuonium : public G4ParticleDefinition {
private:
    static MACE::SimG4::Physics::AntiMuonium* instance;

public:
    static MACE::SimG4::Physics::AntiMuonium* Definition();
    static MACE::SimG4::Physics::AntiMuonium* AntiMuoniumDefinition();
};
