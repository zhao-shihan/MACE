#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidB2Field.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidB2Field::SolenoidB2Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
