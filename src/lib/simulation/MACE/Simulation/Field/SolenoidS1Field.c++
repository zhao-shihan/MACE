#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidS1Field.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidS1Field::SolenoidS1Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
