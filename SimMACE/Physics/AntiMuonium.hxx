#pragma once

#include "SimMACE/Global.hxx"
#include "G4ParticleDefinition.hh"

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
