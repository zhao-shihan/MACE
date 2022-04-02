#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class TransportLine final : public IDescription {
public:
    static TransportLine& Instance() noexcept;

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

    G4Transform3D FirstStraightTransform() const;
    G4Transform3D FirstBendTransform() const;
    G4Transform3D SecondStraightTransform() const;
    G4Transform3D SecondBendTransform() const;
    G4Transform3D ThirdStraightTransform() const;

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
