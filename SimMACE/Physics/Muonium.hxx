#pragma once

#include "G4ParticleDefinition.hh"

#include "SimMACE/Global.hxx"

// Muonium Definition

class MACE::SimMACE::Physics::Muonium : public G4ParticleDefinition {
private:
    static MACE::SimMACE::Physics::Muonium* instance;

public:
    static MACE::SimMACE::Physics::Muonium* Definition();
    static MACE::SimMACE::Physics::Muonium* MuoniumDefinition();
};

