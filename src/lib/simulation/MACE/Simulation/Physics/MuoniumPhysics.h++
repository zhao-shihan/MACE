#pragma once

#include "MACE/Extension/Geant4X/Antimuonium.h++"
#include "MACE/Extension/Geant4X/Muonium.h++"
#include "MACE/Simulation/Physics/Process/MuoniumFormation.h++"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.h++"
#include "MACE/Simulation/Physics/TargetForMuoniumPhysics.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "G4MuonPlus.hh"
#include "G4ProcessManager.hh"
#include "G4VPhysicsConstructor.hh"

namespace MACE::inline Simulation::inline Physics {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysics final : public NonMoveableBase,
                             public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose);

    auto ConstructParticle() -> void override;
    auto ConstructProcess() -> void override;
};

} // namespace MACE::inline Simulation::inline Physics

#include "MACE/Simulation/Physics/MuoniumPhysics.inl"
