#include "MACE/Simulation/Field/SpectrometerFieldMessenger.h++"
#include "MACE/Simulation/Field/SpectrometerField.h++"

namespace MACE::inline Simulation::inline Field {

SpectrometerField::SpectrometerField() :
    WrapAsG4Field{} {
    SpectrometerFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::inline Simulation::inline Field
