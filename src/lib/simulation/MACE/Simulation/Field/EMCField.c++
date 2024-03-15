#include "MACE/Simulation/Field/EMCField.h++"
#include "MACE/Simulation/Field/EMCFieldMessenger.h++"

namespace MACE::inline Simulation::inline Field {

EMCField::EMCField() :
    WrapAsG4Field{} {
    EMCFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
