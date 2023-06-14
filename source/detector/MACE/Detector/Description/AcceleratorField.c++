#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::ElectricPotential;

AcceleratorField::AcceleratorField() :
    DescriptionSingletonBase<AcceleratorField>(__func__),
    // Geometry
    fRadius(75_mm),
    fLength(100_cm),
    fDownStreamLength(60_cm),
    // Field
    fAcceleratorPotential(5_kV),
    // Cached value
    fAcceleratorFieldStrength(fAcceleratorPotential / fDownStreamLength) {}

HepGeom::Transform3D AcceleratorField::CalcTransform() const {
    return HepGeom::Transform3D({}, {0, 0, fDownStreamLength - fLength / 2});
}

void AcceleratorField::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fDownStreamLength, "DownStreamLength");
    // Field
    ImportValue(node, fAcceleratorPotential, "AcceleratorPotential");
}

void AcceleratorField::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fDownStreamLength, "DownStreamLength");
    // Field
    ExportValue(node, fAcceleratorPotential, "AcceleratorPotential");
}

} // namespace MACE::Detector::Description
