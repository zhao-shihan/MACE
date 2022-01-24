#pragma once

#include "SimMACE/Global.hxx"
#include "G4ParticleDefinition.hh"

// AntiMuonium Definition

class MACE::SimMACE::Physics::AntiMuonium : public G4ParticleDefinition {
private:
    static MACE::SimMACE::Physics::AntiMuonium* instance;

public:
    static MACE::SimMACE::Physics::AntiMuonium* Definition();
    static MACE::SimMACE::Physics::AntiMuonium* AntiMuoniumDefinition();
};
