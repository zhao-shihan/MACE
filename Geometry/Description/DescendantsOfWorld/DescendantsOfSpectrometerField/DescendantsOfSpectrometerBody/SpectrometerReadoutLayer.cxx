#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"

using namespace MACE::Geometry::Description;

SpectrometerReadoutLayer& SpectrometerReadoutLayer::Instance() noexcept {
    static SpectrometerReadoutLayer instance;
    return instance;
}
