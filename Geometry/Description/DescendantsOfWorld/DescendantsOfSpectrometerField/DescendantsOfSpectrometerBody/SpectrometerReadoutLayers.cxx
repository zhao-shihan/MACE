#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"

using namespace MACE::Geometry::Description;

SpectrometerReadoutLayers& SpectrometerReadoutLayers::Instance() noexcept {
    static SpectrometerReadoutLayers instance;
    return instance;
}
