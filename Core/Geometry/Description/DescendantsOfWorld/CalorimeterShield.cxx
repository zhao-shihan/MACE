#include "Geometry/Description/DescendantsOfWorld/CalorimeterShield.hxx"

using namespace MACE::Geometry::Description;

CalorimeterShield& CalorimeterShield::Instance() noexcept {
    static CalorimeterShield instance;
    return instance;
}
