#pragma once

#include "Core/Geometry/Description/SecondTransportField.hxx"

#include "G4Transform3D.hh"

namespace MACE::Core::Geometry::Description {

class SecondBendField final : public IDescription {
public:
    static SecondBendField& Instance() noexcept;

private:
    SecondBendField();
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

public:
    const auto& GetRadius() const { return SecondTransportField::Instance().GetRadius(); }
    const auto& GetBendRadius() const { return fBendRadius; }
    G4Transform3D GetTransform() const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius;
};

} // namespace MACE::Core::Geometry::Description
