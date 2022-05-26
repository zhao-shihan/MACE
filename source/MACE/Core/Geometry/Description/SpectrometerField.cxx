#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}

SpectrometerField::SpectrometerField() :
    IDescription("SpectrometerField"),
    fRadius(71_cm),
    fLength(220_cm) {}

void SpectrometerField::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "Radius", fRadius);
    ReadValueNode(node, "Length", fLength);
}

void SpectrometerField::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "Radius", fRadius);
    WriteValueNode(node, "Length", fLength);
}

} // namespace MACE::Core::Geometry::Description
