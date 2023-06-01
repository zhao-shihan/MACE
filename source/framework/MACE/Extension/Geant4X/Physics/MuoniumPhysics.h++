#pragma once

#include "MACE/Extension/Geant4X/Physics/Particle/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Physics/Particle/Muonium.h++"
#include "MACE/Extension/Geant4X/Physics/Process/MuoniumFormation.h++"
#include "MACE/Extension/Geant4X/Physics/Process/MuoniumTransport.h++"
#include "MACE/Extension/Geant4X/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"
#include "G4VPhysicsConstructor.hh"

namespace MACE::inline Extension::Geant4X::Physics {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysics final : public NonMoveableBase,
                             public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose);

    void ConstructParticle() override;
    void ConstructProcess() override;
};

} // namespace MACE::inline Extension::Geant4X::Physics

#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.inl"
