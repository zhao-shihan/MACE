#pragma once

#include "G4ParticleDefinition.hh"
#include "SimMACE/Global.hxx"

class MACE::SimMACE::Physics::AntiMuonium final :
    public G4ParticleDefinition {
public:
    static AntiMuonium* Definition();

private:
    static AntiMuonium* fgInstance;

private:
    AntiMuonium();

public:
    ~AntiMuonium() noexcept = default;
};
