#include "MACE/Simulation/Field/MMSFieldMessenger.h++"
#include "MACE/Simulation/Field/MMSField.h++"

namespace MACE::inline Simulation::inline Field {

MMSField::MMSField() :
    WrapAsG4Field{} {
    MMSFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
