#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidS3Field.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidS3Field::SolenoidS3Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
