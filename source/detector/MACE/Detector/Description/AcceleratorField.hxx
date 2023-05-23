#pragma once

#include "MACE/Detector/Description/DescriptionBase.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Detector::Description {

class AcceleratorField final : public DescriptionSingletonBase<AcceleratorField> {
    friend Env::Memory::SingletonFactory;

private:
    AcceleratorField();

public:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    const auto& Radius() const { return fRadius; }
    const auto& Length() const { return fLength; }
    const auto& DownStreamLength() const { return fDownStreamLength; }

    void Radius(auto v) { fRadius = v; }
    void Length(auto v) { fLength = v; }
    void DownStreamLength(auto v) { (fDownStreamLength = v, UpdateAcceleratorFieldStrength()); }

    HepGeom::Transform3D CalcTransform() const;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    const auto& AcceleratorPotential() const { return fAcceleratorPotential; }

    void AcceleratorPotential(auto v) { (fAcceleratorPotential = v, UpdateAcceleratorFieldStrength()); }

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    const auto& AcceleratorFieldStrength() const { return fAcceleratorFieldStrength; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

    void UpdateAcceleratorFieldStrength() { fAcceleratorFieldStrength = fAcceleratorPotential / fDownStreamLength; }

private:
    ///////////////////////////////////////////////////////////
    // Geometry
    ///////////////////////////////////////////////////////////

    double fRadius;
    double fLength;
    double fDownStreamLength;

    ///////////////////////////////////////////////////////////
    // Field
    ///////////////////////////////////////////////////////////

    double fAcceleratorPotential;

    ///////////////////////////////////////////////////////////
    // Cached value
    ///////////////////////////////////////////////////////////

    double fAcceleratorFieldStrength;
};

} // namespace MACE::Detector::Description
