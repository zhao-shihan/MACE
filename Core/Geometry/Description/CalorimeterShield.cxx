#include "Core/Geometry/Description/CalorimeterShield.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

CalorimeterShield& CalorimeterShield::Instance() noexcept {
    static CalorimeterShield instance;
    return instance;
}

CalorimeterShield::CalorimeterShield() :
    IDescription("CalorimeterShield"),
    fInnerRadius(30_cm),
    fInnerLength(80_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

} // namespace MACE::Core::Geometry::Description
