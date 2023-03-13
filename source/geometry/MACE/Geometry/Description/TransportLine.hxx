#pragma once

#include "MACE/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Geometry::Description {

class TransportLine final : public ISingletonDescription<TransportLine> {
    friend Env::Memory::SingletonFactory;

private:
    TransportLine();
    ~TransportLine() noexcept = default;
    TransportLine(const TransportLine&) = delete;
    TransportLine& operator=(const TransportLine&) = delete;

public:
    const auto& FirstStraightLength() const { return fFirstStraightLength; }
    const auto& FirstBendRadius() const { return fFirstBendRadius; }
    const auto& SecondStraightLength() const { return fSecondStraightLength; }
    const auto& SecondBendRadius() const { return fSecondBendRadius; }
    const auto& ThirdStraightLength() const { return fThirdStraightLength; }
    const auto& SolenoidInnerRadius() const { return fSolenoidInnerRadius; }
    const auto& SolenoidOuterRadius() const { return fSolenoidOuterRadius; }
    const auto& FieldRadius() const { return fFieldRadius; }

    void FirstStraightLength(double val) { fFirstStraightLength = val; }
    void FirstBendRadius(double val) { fFirstBendRadius = val; }
    void SecondStraightLength(double val) { fSecondStraightLength = val; }
    void SecondBendRadius(double val) { fSecondBendRadius = val; }
    void ThirdStraightLength(double val) { fThirdStraightLength = val; }
    void SolenoidInnerRadius(double val) { fSolenoidInnerRadius = val; }
    void SolenoidOuterRadius(double val) { fSolenoidOuterRadius = val; }
    void FieldRadius(double val) { fFieldRadius = val; }

    // Next 5 methods should only use for geometry construction.

    HepGeom::Transform3D FirstStraightTransform() const;
    HepGeom::Transform3D FirstBendTransform() const;
    HepGeom::Transform3D SecondStraightTransform() const;
    HepGeom::Transform3D SecondBendTransform() const;
    HepGeom::Transform3D ThirdStraightTransform() const;

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fFirstStraightLength;
    double fFirstBendRadius;
    double fSecondStraightLength;
    double fSecondBendRadius;
    double fThirdStraightLength;
    double fSolenoidInnerRadius;
    double fSolenoidOuterRadius;
    double fFieldRadius;
};

} // namespace MACE::Geometry::Description
