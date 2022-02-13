#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"

using namespace MACE::Geometry::Description;

SpectrometerCells& SpectrometerCells::Instance() {
    static SpectrometerCells instance;
    return instance;
}
