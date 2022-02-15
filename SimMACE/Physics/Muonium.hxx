#pragma once

#include "G4ParticleDefinition.hh"

#include "SimMACE/Global.hxx"

// Muonium Definition

class MACE::SimMACE::Physics::Muonium final :
    public G4ParticleDefinition {
public:
    static Muonium* Definition();
private:
    static Muonium* fgInstance;

private:
    Muonium();

public:
    ~Muonium() noexcept = default;
};
