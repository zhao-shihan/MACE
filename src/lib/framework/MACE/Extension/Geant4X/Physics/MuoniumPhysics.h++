#pragma once

#include "MACE/Extension/Geant4X/Particle/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Particle/Muonium.h++"
#include "MACE/Extension/Geant4X/Process/MuoniumFormation.h++"
#include "MACE/Extension/Geant4X/Process/MuoniumTransport.h++"
#include "MACE/Extension/Geant4X/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4EmBuilder.hh"
#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"
#include "G4VPhysicsConstructor.hh"

namespace MACE::inline Extension::Geant4X::inline Physics {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysics final : public NonMoveableBase,
                             public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose);

    auto ConstructParticle() -> void override;
    auto ConstructProcess() -> void override;
};

} // namespace MACE::inline Extension::Geant4X::inline Physics

#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.inl"
