#include "G4ProcessManager.hh"
#include "G4MuonPlus.hh"

#include "physics/PhysicsList.hh"
#include "physics/MuoniumPhysics.hh"

using namespace MACE::SimG4::Physics;

PhysicsList::PhysicsList(G4int verbose) :
    FTFP_BERT(verbose),
    fVerbose(verbose) {
    RegisterPhysics(new MuoniumPhysics());
}
