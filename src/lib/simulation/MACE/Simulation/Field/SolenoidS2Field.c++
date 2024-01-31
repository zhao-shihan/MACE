#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidS2Field.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidS2Field::SolenoidS2Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
