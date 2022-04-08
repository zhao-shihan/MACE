#include "MACE/Core/Geometry/Description/EMCal.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

EMCal& EMCal::Instance() noexcept {
    static EMCal instance;
    return instance;
}

EMCal::EMCal() :
    IDescription("EMCal"),
    fInnerRadius(15_cm),
    fInnerLength(50_cm),
    fWindowRadius(8_cm),
    fCrystalLength(5_cm) {}

void EMCal::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fInnerLength = node["InnerRadius"].as<decltype(fInnerLength)>();
    fWindowRadius = node["WindowRadius"].as<decltype(fWindowRadius)>();
    fCrystalLength = node["CrystalLength"].as<decltype(fCrystalLength)>();
}

void EMCal::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["InnerLength"] = fInnerLength;
    node["WindowRadius"] = fWindowRadius;
    node["CrystalLength"] = fCrystalLength;
}

} // namespace MACE::Core::Geometry::Description
