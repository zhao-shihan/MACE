#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidFieldS1.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldS1::SolenoidFieldS1() :
    AsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
