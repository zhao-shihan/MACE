#include "Core/Geometry/Description/CalorimeterShield.hxx"

using MACE::Geometry::Description::CalorimeterShield;

CalorimeterShield& CalorimeterShield::Instance() noexcept {
    static CalorimeterShield instance;
    return instance;
}
