#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"

using namespace MACE::Geometry::Description;

FirstTransportField& FirstTransportField::Instance() {
    static FirstTransportField instance;
    return instance;
}
