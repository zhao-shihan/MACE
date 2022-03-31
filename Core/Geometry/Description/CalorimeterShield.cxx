#include "Core/Geometry/Description/CalorimeterShield.hxx"

using MACE::Core::Geometry::Description::CalorimeterShield;

CalorimeterShield& CalorimeterShield::Instance() noexcept {
    static CalorimeterShield instance;
    return instance;
}
