#include "Core/Geometry/Description/SpectrometerField.hxx"

using MACE::Core::Geometry::Description::SpectrometerField;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}
