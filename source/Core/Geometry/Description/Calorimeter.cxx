#include "Core/Geometry/Description/Calorimeter.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Calorimeter& Calorimeter::Instance() noexcept {
    static Calorimeter instance;
    return instance;
}

Calorimeter::Calorimeter() :
    IDescription("Calorimeter"),
    fInnerRadius(15_cm),
    fInnerLength(50_cm),
    fWindowRadius(8_cm),
    fCrystalLength(5_cm) {}

void Calorimeter::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fInnerLength = node["InnerRadius"].as<decltype(fInnerLength)>();
    fWindowRadius = node["WindowRadius"].as<decltype(fWindowRadius)>();
    fCrystalLength = node["CrystalLength"].as<decltype(fCrystalLength)>();
}

void Calorimeter::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["InnerLength"] = fInnerLength;
    node["WindowRadius"] = fWindowRadius;
    node["CrystalLength"] = fCrystalLength;
}

} // namespace MACE::Core::Geometry::Description
