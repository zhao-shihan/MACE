#pragma once

#include "G4ParticleDefinition.hh"

#include "SimG4/Global.hxx"

// Muonium Definition

class MACE::SimG4::Physics::Muonium : public G4ParticleDefinition {
private:
    static MACE::SimG4::Physics::Muonium* instance;

public:
    static MACE::SimG4::Physics::Muonium* Definition();
    static MACE::SimG4::Physics::Muonium* MuoniumDefinition();
};

