#include "Geometry/Description/DescendantsOfWorld/CalorimeterField.hxx"

using namespace MACE::Geometry::Description;

CalorimeterField& CalorimeterField::Instance() {
    static CalorimeterField instance;
    return instance;
}
