#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"

using namespace MACE::Geometry::Description;

SpectrometerCells& SpectrometerCells::Instance() noexcept {
    static SpectrometerCells instance;
    return instance;
}
