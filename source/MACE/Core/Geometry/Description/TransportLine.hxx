#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

#include "CLHEP/Geometry/Transform3D.h"

namespace MACE::Core::Geometry::Description {

class TransportLine final : public IDescriptionSingleton<TransportLine> {
    friend Environment::Resource::SingletonFactory;

private:
    TransportLine();
    ~TransportLine() noexcept = default;
    TransportLine(const TransportLine&) = delete;
    TransportLine& operator=(const TransportLine&) = delete;

public:
    const auto& GetFirstStraightLength() const { return fFirstStraightLength; }
    const auto& GetFirstBendRadius() const { return fFirstBendRadius; }
    const auto& GetSecondStraightLength() const { return fSecondStraightLength; }
    const auto& GetSecondBendRadius() const { return fSecondBendRadius; }
    const auto& GetThirdStraightLength() const { return fThirdStraightLength; }
    const auto& GetSolenoidInnerRadius() const { return fSolenoidInnerRadius; }
    const auto& GetSolenoidOuterRadius() const { return fSolenoidOuterRadius; }
    const auto& GetFieldRadius() const { return fFieldRadius; }

    void SetFirstStraightLength(double val) { fFirstStraightLength = val; }
    void SetFirstBendRadius(double val) { fFirstBendRadius = val; }
    void SetSecondStraightLength(double val) { fSecondStraightLength = val; }
    void SetSecondBendRadius(double val) { fSecondBendRadius = val; }
    void SetThirdStraightLength(double val) { fThirdStraightLength = val; }
    void SetSolenoidInnerRadius(double val) { fSolenoidInnerRadius = val; }
    void SetSolenoidOuterRadius(double val) { fSolenoidOuterRadius = val; }
    void SetFieldRadius(double val) { fFieldRadius = val; }

    // Next 5 methods should only use for geometry construction.

    HepGeom::Transform3D FirstStraightTransform() const;
    HepGeom::Transform3D FirstBendTransform() const;
    HepGeom::Transform3D SecondStraightTransform() const;
    HepGeom::Transform3D SecondBendTransform() const;
    HepGeom::Transform3D ThirdStraightTransform() const;

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

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

} // namespace MACE::Core::Geometry::Description
