#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidFieldB1.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldB1::SolenoidFieldB1() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
