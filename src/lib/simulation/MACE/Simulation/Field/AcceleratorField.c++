#include "MACE/Simulation/Field/AcceleratorField.h++"
#include "MACE/Simulation/Field/AcceleratorFieldMessenger.h++"

namespace MACE::inline Simulation::inline Field {

AcceleratorField::AcceleratorField() :
    WrapAsG4Field{} {
    AcceleratorFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
