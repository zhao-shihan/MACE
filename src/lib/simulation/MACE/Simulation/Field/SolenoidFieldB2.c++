#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidFieldB2.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldB2::SolenoidFieldB2() :
    AsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
