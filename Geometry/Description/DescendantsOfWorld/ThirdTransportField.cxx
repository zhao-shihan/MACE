#include "Geometry/Description/DescendantsOfWorld/ThirdTransportField.hxx"

using namespace MACE::Geometry::Description;

ThirdTransportField& ThirdTransportField::Instance() noexcept {
    static ThirdTransportField instance;
    return instance;
}
