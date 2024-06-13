#include "MACE/Simulation/Field/SolenoidFieldMessenger.h++"
#include "MACE/Simulation/Field/SolenoidFieldS3.h++"

namespace MACE::inline Simulation::inline Field {

SolenoidFieldS3::SolenoidFieldS3() :
    AsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
