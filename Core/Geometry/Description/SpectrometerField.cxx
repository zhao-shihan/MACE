#include "Geometry/Description/SpectrometerField.hxx"

using MACE::Geometry::Description::SpectrometerField;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}
