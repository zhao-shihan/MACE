#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidFieldS2.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldS2::SolenoidFieldS2() :
    AsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
