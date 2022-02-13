#include "Geometry/Description/DescendantsOfWorld/ThirdTransportField.hxx"

using namespace MACE::Geometry::Description;

ThirdTransportField& ThirdTransportField::Instance() {
    static ThirdTransportField instance;
    return instance;
}
